/*
https://leetcode.com/problems/lfu-cache/

460. LFU Cache
Design and implement a data structure for Least Frequently Used (LFU) cache. It should support the following operations: get and set.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
set(key, value) - Set or insert the value if the key is not already present. When the cache reaches its capacity, it should invalidate the least frequently used item before inserting a new item. For the purpose of this problem, when there is a tie (i.e., two or more keys that have the same frequency), the least recently used key would be evicted.

Follow up:
Could you do both operations in O(1) time complexity?

Example:

LFUCache cache = new LFUCache(2); // capacity is 2

cache.set(1, 1);
cache.set(2, 2);
cache.get(1);       // returns 1
cache.set(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.get(3);       // returns 3.
cache.set(4, 4);    // evicts key 1.
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4
*/
	
class LFUCache {
public:
	struct Node {
		Node(int key, int val) : key(key), val(val), freq(1) {}
		int key;
		int val;
		int freq;

		bool operator=(const Node* node) const {
			return key == node->key;
		}
	};

	LFUCache(int capacity) : m_capacity(capacity) {

	}

	int get(int key) 
	{
	    int val = -1;
		const auto& it = m_mapNodes.find(key);
		if (it != m_mapNodes.end()) 
		{
			Node* pNode = it->second;
			update(pNode);
			val = pNode->val;
		}

        //cout << "get: " << key << "=" << val << endl;
        //dump();
		return val;
	}

	void set(int key, int value) 
	{
		const auto& it = m_mapNodes.find(key);
		if (it != m_mapNodes.end()) 
		{
			Node* pNode = it->second;
			pNode->val = value; // Update value
			update(pNode); // Update frequency map
		} 
		else // not exists, a new one
		{
			if (m_mapNodes.size() >= m_capacity)
			{
				checkCapacity(); // Check capacity first, if there is no enough space, remove the least frequently used one
			}			

			if (m_mapNodes.size() < m_capacity)
			{
				Node* pNode = new Node(key, value);
				m_mapNodes[key] = pNode;
				m_mapFreq[pNode->freq].push_front(pNode);
			}			
		}
		//cout << "set: (" << key << ", " << value << ")" << endl;
		//dump();
	}

private:
	void update(Node* pNode) 
	{
		// Before update, need to find the node in the freq map, so that we remove it from the map
		int freq = pNode->freq;
		const auto& itFreq = m_mapFreq.find(freq);
		if (itFreq != m_mapFreq.end()) 
		{		
			const auto& itDelete = find(m_mapFreq[freq].begin(), m_mapFreq[freq].end(), pNode);
			if (itDelete != m_mapFreq[freq].end()) 
			{
				m_mapFreq[freq].erase(itDelete);
				if (m_mapFreq[freq].size() == 0) 
				{
					m_mapFreq.erase(itFreq);
				}
			}
		}

		++pNode->freq; // Update frequency
		// According to the new frequency, push to the front, which is most frequently used
		m_mapFreq[pNode->freq].push_front(pNode);
		if (pNode->freq > m_max_freq)
			m_max_freq = pNode->freq; // Update maximum frequency
	}

	void checkCapacity()
	{
		int freq = 1;
		while (true) 
		{
			const auto& itFreq = m_mapFreq.find(freq);
			if (itFreq == m_mapFreq.end())
			{
				++freq;
				if (freq > m_max_freq)
					return;
				continue;
			}

			if (m_mapFreq[freq].size() == 0)
			{
				m_mapFreq.erase(itFreq);
				++freq;
				continue;
			}

			Node* pNode = m_mapFreq[freq].back();
			m_mapFreq[freq].pop_back();
			const auto& itDelete = m_mapNodes.find(pNode->key);
			if (itDelete != m_mapNodes.end())
			{
				m_mapNodes.erase(itDelete);
			}
			delete pNode;
			break;
		}
	}
	
	void dump()
	{
	    for (const auto& kv : m_mapNodes)
	    {
	        cout << "(" << kv.first << ", " << kv.second->val << ", " << kv.second->freq << ")" << endl;
	    }
	    cout << "----------------------------------------" << endl;
	}

private:
	// Use a double link list to store the cache
	// The most frequently used node will be put to the head
	// the least frequently used node will be put to the tail
	int m_capacity;
	// Use a hash map to map the key to the node, so that we can find the node in O(1) time complexity
	unordered_map<int, Node*> m_mapNodes; // Key to Node
	unordered_map<int, deque<Node*>> m_mapFreq; // Freq to Node list
	int m_max_freq;
};
