/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:21:42 by dselmy            #+#    #+#             */
/*   Updated: 2023/06/20 17:57:08 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
	timeMsLst = -1.0;
	timeMsVct = -1.0;
}

PmergeMe::PmergeMe(const PmergeMe & rhs)
{
	*this = rhs;
}

PmergeMe & PmergeMe::operator= (const PmergeMe & rhs)
{
	initLst.clear();
	initLst = rhs.initLst;

	initVct.clear();
	initVct = rhs.initVct;

	timeMsLst = rhs.timeMsLst;

	resLst.clear();
	resLst = rhs.resLst;

	resVct.clear();
	resVct = rhs.resVct;

	timeMsVct = rhs.timeMsVct;

	return *this;
}

PmergeMe::~PmergeMe() {}

static void putVct(const std::vector<int> & vct) {
	for (size_t i = 0; i < vct.size(); i++) {
		std::cout << vct[i] << " ";
	}
	std::cout << std::endl;
}

static void putLst(const std::list<int> & lst)
{
	for (std::list<int>::const_iterator it = lst.begin(); it != lst.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::sortVct(int argc, char ** argv)
{
	std::clock_t start = std::clock();
	if (start == std::clock_t(-1))
		return;
	processNumbers(argc, argv, initVct);

	if (initVct.size() <= 1) {
		resVct = initVct;
		timeMsVct = makeTime(start);
		return;
	}
	int staggler = 0;
	if (initVct.size() % 2 == 1) {
		staggler = initVct.back();
		initVct.pop_back();
	}

	std::vector< std::vector<int> > pairs;
	makePairs(pairs);
	sortEachPair(pairs);
	sortInsert(pairs, pairs.size() - 1);
	mergePairs(pairs);

	if (staggler > 0) {
		initVct.push_back(staggler);
		resVct.insert(std::upper_bound(resVct.begin(), resVct.end(), staggler), staggler);
	}

	std::clock_t end = std::clock();
	if (end == std::clock_t(-1))
		return;
	timeMsVct = makeTime(start);
}

/*
	Methods for sorting using std::vector
*/

void PmergeMe::makePairs(std::vector< std::vector<int> > & pairs)
{
	std::vector<int> tmp;
	for (size_t i = 0; i < initVct.size(); i++) {
		tmp.push_back(initVct[i]);
		if (tmp.size() == 2) {
			pairs.push_back(tmp);
			tmp.clear();
		}
	}
}

void PmergeMe::sortEachPair(std::vector< std::vector<int> > & pairs)
{
	for (size_t i = 0; i < pairs.size(); i++) {
		std::vector<int> & pair = pairs[i];
		if (pair.front() > pair.back()) {
			std::swap(pair[0], pair[1]);
		}
	}
}

void PmergeMe::sortInsert(std::vector< std::vector<int> > & pairs, size_t right)
{
	if (right < 1)
		return;
	sortInsert(pairs, right - 1);

	std::vector<int> key_right = pairs[right];
	int left = right - 1;

	while (left >= 0 && comparePairsVct(key_right, pairs[left])) { // changed comparePairs prototype
		pairs[left + 1] = pairs[left];
		left -= 1;
	}
	pairs[left + 1] = key_right;
}

std::vector<int> PmergeMe::makePend(std::vector< std::vector<int> > & pairs)
{
	std::vector<int> pend;

	resVct.reserve(initVct.size());
	resVct.push_back(pairs[0][0]);
	resVct.push_back(pairs[0][1]);

	for (size_t i = 1; i < pairs.size(); i++) {
		int resValue = pairs[i][1];
		int pendValue = pairs[i][0];
		resVct.push_back(resValue);
		pend.push_back(pendValue);
	}
	return pend;
}

void PmergeMe::mergePend(std::vector<int> & pend, std::vector<int> & orderingSequence)
{
	size_t i = 0;
	for (std::vector<int>::iterator it = orderingSequence.begin(); it != orderingSequence.end(); it++) {
		int groupSize = *it;
		while (groupSize > 0) {
			int index = groupSize - 1 + i;
			int resIndex = index + i + 2;
			groupSize -= 1;
			resVct.insert(std::upper_bound(resVct.begin(), resVct.begin() + resIndex, pend[index]), pend[index]);
		}
		i += *it;
	}
}

void PmergeMe::mergePairs(std::vector< std::vector<int> > & pairs)
{
	std::vector<int> pend = makePend(pairs);

	std::vector<int> orderingSequence = 
					makeOrderingSequence< std::vector<int> >(pend.size());
	mergePend(pend, orderingSequence);
}

/*
	Methods for sorting using std::list
*/

void PmergeMe::sortLst(int argc, char ** argv)
{
	std::clock_t start = std::clock();
	if (start == std::clock_t(-1))
		return;
	
	processNumbers(argc, argv, initLst);
	
	if (initLst.size() == 1) {
		resLst = initLst;
		timeMsLst = makeTime(start);
		return;
	}

	int staggler = 0;
	if (initVct.size() % 2 == 1) {
		staggler = initLst.back();
		initLst.pop_back();
	}

	
	std::list< std::list<int> > pairs;
	makePairs(pairs);

	std::cout << std::endl;
	sortEachPair(pairs);
	sortInsert(pairs);
	mergePairs(pairs);

	if (staggler > 0) {
		initLst.push_back(staggler);
		resLst.insert(std::upper_bound(resLst.begin(), resLst.end(), staggler), staggler);
	}
	timeMsLst = makeTime(start);
}

void PmergeMe::makePairs(std::list< std::list<int> > & pairs)
{
	std::list<int> tmp;
	for (std::list<int>::iterator it = initLst.begin(); it != initLst.end(); it++)
	{
		tmp.push_back(*it);
		if (tmp.size() == 2) {
			pairs.push_back(tmp);
			tmp.clear();
		}
	}
}
void PmergeMe::sortEachPair(std::list< std::list<int> > & pairs)
{
	for (std::list< std::list<int> >::iterator it = pairs.begin();
													it != pairs.end(); it++)
	{
		std::list<int> & pair = *it;
		if (pair.front() > pair.back()) {
			std::swap(pair.front(), pair.back());
		}
	}
}

void PmergeMe::sortInsert(std::list< std::list<int> > & pairs)
{
	// iterator to the next element to insert
	// and to erase it from the initial position
	std::list< std::list<int> >::iterator itPos = ++(pairs.begin());
	
	// temporary iterator to preserve the end of the sorted sequence
	// after erasing the inserted element from its initial position
	std::list< std::list<int> >::iterator itSorted (itPos);

	while(itPos != pairs.end()) {
		std::list<int> keyToInsert = *itSorted;
		itSorted++;
		pairs.erase(itPos);
		pairs.insert(std::upper_bound(pairs.begin(), itSorted, keyToInsert, comparePairsLst), keyToInsert);
		itPos = itSorted;
	}
}

void PmergeMe::mergePairs(std::list< std::list<int> > & pairs)
{
	std::list<int> pend = makePend(pairs);

	std::list<int> orderingSequence =
					makeOrderingSequence< std::list<int> >(pend.size());

	mergePend(pend, orderingSequence);
}

void PmergeMe::mergeGroup(std::list<int>::iterator pendIt, std::list<int>::iterator resIt, size_t n)
{
	while (n > 0) {
		// std::cout << "Inserting a " << *pendIt << " before the " << *resIt << std::endl;
		std::list<int>::iterator nextRes = resIt;
		nextRes--;
		resLst.insert(std::upper_bound(resLst.begin(), resIt, *pendIt), *pendIt);	
		resIt = nextRes;
		pendIt--;
		n--;
	}
}

void PmergeMe::mergePend(std::list<int> & pend, std::list<int> & orderingSequence)
{
	std::list<int>::iterator it = pend.begin();
	std::list<int>::iterator biggerPairIt = resLst.begin();
	biggerPairIt++;
	biggerPairIt++;

	// we move an iterator 
	// we iterate through a group backwards
	// insert each element [begin, according bigger element];
	// to keep track of this bigger element we can keep an iterator to it
	for (std::list<int>::iterator groupsIt = orderingSequence.begin();
									groupsIt != orderingSequence.end(); groupsIt++)
	{
		for (int n = 0; n < *groupsIt - 1; n++) {
			it++;
			biggerPairIt++;
		}
		mergeGroup(it, biggerPairIt, (*groupsIt));

		it++;
		biggerPairIt++;
	}
}

std::list<int> PmergeMe::makePend(std::list< std::list<int> > & pairs)
{
	std::list<int> pend;

	resLst.push_back(pairs.front().front());
	resLst.push_back(pairs.front().back());
	
	pairs.pop_front();
	for (std::list< std::list<int> >::iterator it = pairs.begin();
							it != pairs.end(); it++)
	{
		int resValue = (*it).back();
		int pendValue = (*it).front();
		resLst.push_back(resValue);
		pend.push_back(pendValue);
	}
	return pend;
}

/*
	Output methods
*/

void PmergeMe::print() const
{
	if (initVct.empty() && initLst.empty()) {
		std::cout << "Nothing was processed" <<std::endl;
		return;
	}
	std::cout << "Before: ";
	if (!initVct.empty()) {
		putVct(initVct);
		std::cout << "After: ";
		putVct(resVct);
	}
	else {
		putLst(initLst);
		std::cout << "After: ";
		putLst(resLst);
	}
	putTime();
}

/*
	Helper methods
*/

double PmergeMe::makeTime(const std::clock_t & start) const {
	std::clock_t end = std::clock();
	if (end == std::clock_t(-1))
		return -1;
	return 1000.0 * (end - start) / CLOCKS_PER_SEC;
}

void PmergeMe::putTime() const
{
	if (timeMsVct > 0.0) {
		size_t size = resVct.size();
		std::cout << "Time to process a range of "
				<< size << " elements with std::vector : "
				<< timeMsVct << " ms" << std::endl;
	}
	if (timeMsLst > 0.0) {
		size_t size = resLst.size();
		std::cout << "Time to process a range of "
				<< size << " elements with std::list: "
				<< timeMsLst << " ms" << std::endl;
	}
}

/*Comparison function that returns True if left < right*/
bool PmergeMe:: comparePairsLst(const std::list<int> & left, const std::list<int> & right)
{
	return left.back() < right.back();
}

/*Comparison function that returns True if left < right*/
bool PmergeMe:: comparePairsVct(const std::vector<int> & left, const std::vector<int> & right)
{
	return left.back() < right.back();
}
