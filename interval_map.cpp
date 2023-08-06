#include <bits/stdc++.h>
using namespace std;
template <typename K, typename V>
class interval_map
{
	friend void IntervalMapTest();
	V m_valBegin;
	std::map<K, V> m_map;

public:
	// constructor associates whole range of K with val
	interval_map(V const &val)
		: m_valBegin(val)
	{
	}

	// Assign value val to interval [keyBegin, keyEnd).
	// Overwrite previous values in this interval.
	// Conforming to the C++ Standard Library conventions, the interval
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval,
	// and assign must do nothing.
	void assign(K const &keyBegin, K const &keyEnd, V const &val)
	{
		if (!(keyBegin < keyEnd))
		{
			return;
		}
		if (m_map.size() == 0)
		{
			if (m_valBegin == val)
			{	
				//do nothing
			}else{
                m_map.insert({keyBegin,val});
				m_map.insert({keyEnd,m_valBegin});
			}
			return;
		}
		auto kbl = m_map.lower_bound(keyBegin);
		auto kbu=m_map.upper_bound(keyBegin);
		auto kel = m_map.lower_bound(keyEnd);
		auto keu = m_map.upper_bound(keyEnd);
		--keu;
		if (kbl == m_map.end())
		{
			if (val != m_valBegin)
			{
				m_map.insert({keyBegin,val});
			}else{
				return;
			}
		}
		else
		{
			m_map.insert({keyBegin,val});
		}
		auto keu_temp = keu;
		V temp_val2;
		temp_val2 = m_valBegin;
		if (keu != m_map.end())
		{
			temp_val2 = keu->second;
		}
		for (auto it = keu; it->first > keyBegin;)
		{
			auto it2 = it;
			it = m_map.erase(it2);
			--it;
		}
		m_map.insert({keyEnd,temp_val2});
	}
	// look-up of the value associated with key
	V const &operator[](K const &key) const
	{
		auto it = m_map.upper_bound(key);
		if (it == m_map.begin())
		{
			return m_valBegin;
		}
		else
		{
			return (--it)->second;
		}
	}
};

void IntervalMapTest()
{
	interval_map<int, char> map('A');
	cout << "hi" << endl;
	map.assign(1, 4, 'A');
	map.assign(7, 10, 'C');
	map.assign(5, 6, 'X');
	map.assign(-1,13,'Y');
	for (int i = -2; i <= 17; i++)
	{
		cout << i << "-->" << map[i] << endl;
	}
}

int main()
{
	IntervalMapTest();
	return 0;
}

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.