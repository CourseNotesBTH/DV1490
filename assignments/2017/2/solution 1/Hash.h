#ifndef HASH_H
#define HASH_H

// function object template
template <typename Key>
class Hash
{
public:
	unsigned int operator()(const Key & key) const;  
};


#endif