/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:21:42 by dselmy            #+#    #+#             */
/*   Updated: 2023/07/05 01:54:22 by dselmy           ###   ########.fr       */
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

static void putVct(const std::vector<unsigned> & vct)
{
	for (size_t i = 0; i < vct.size(); i++) {
		std::cout << vct[i] << " ";
	}
	std::cout << std::endl;
}

static void putLst(const std::list<unsigned> & lst)
{
	for (std::list<unsigned>::const_iterator it = lst.begin(); it != lst.end(); it++) {
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
	unsigned staggler = 0;
	if (initVct.size() % 2 == 1) {
		staggler = initVct.back();
		initVct.pop_back();
	}

	std::vector< std::vector<unsigned> > pairs;
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

void PmergeMe::makePairs(std::vector< std::vector<unsigned> > & pairs)
{
	std::vector<unsigned> tmp;
	for (size_t i = 0; i < initVct.size(); i++) {
		tmp.push_back(initVct[i]);
		if (tmp.size() == 2) {
			pairs.push_back(tmp);
			tmp.clear();
		}
	}
}

/*Sorts each pair in ascending order*/
void PmergeMe::sortEachPair(std::vector< std::vector<unsigned> > & pairs)
{
	for (size_t i = 0; i < pairs.size(); i++) {
		std::vector<unsigned> & pair = pairs[i];
		if (pair.front() > pair.back()) {
			std::swap(pair[0], pair[1]);
		}
	}
}

/*Sorts pairs depending on the value of the bigger element*/
void PmergeMe::sortInsert(std::vector< std::vector<unsigned> > & pairs, size_t right)
{
	if (right < 1)
		return;
	sortInsert(pairs, right - 1);

	std::vector<unsigned> key_right = pairs[right];
	int left = right - 1;

	while (left >= 0 && comparePairsVct(key_right, pairs[left])) { // changed comparePairs prototype
		pairs[left + 1] = pairs[left];
		left -= 1;
	}
	pairs[left + 1] = key_right;
}

std::vector<unsigned> PmergeMe::makePend(std::vector< std::vector<unsigned> > & pairs)
{
	std::vector<unsigned> pend;

	resVct.reserve(initVct.size());
	
	// the first pair can be considered already sorted and 
	// we don't need to take it into consideration
	resVct.push_back(pairs[0][0]);
	resVct.push_back(pairs[0][1]);

	for (size_t i = 1; i < pairs.size(); i++) {
		unsigned resValue = pairs[i][1];
		unsigned pendValue = pairs[i][0];
		resVct.push_back(resValue);
		pend.push_back(pendValue);
	}
	return pend;
}

void PmergeMe::mergePend(std::vector<unsigned> & pend, std::vector<unsigned> & orderingSequence)
{
	// pend[index] - number of elements already inserted
	size_t elementsInserted = 0;
	
	// take groups of the size according to the ordering sequence from pend
	// and iterate it in reverse
	for (std::vector<unsigned>::iterator it = orderingSequence.begin(); it != orderingSequence.end(); it++) {
		size_t groupSize = *it;
		// pend[index] - the element to be inserted next
		size_t index = groupSize - 1 + elementsInserted;
		// index where the bigger value from the pair lies
		// upperbound of the range to look for the place to insert
		size_t resIndex = 2 + index + elementsInserted;
		
		for (size_t j = 0; j < groupSize; j++) {
			unsigned elementToInsert = pend[index];
			resVct.insert(std::upper_bound(resVct.begin(), resVct.begin() + resIndex, elementToInsert), elementToInsert);
			index--;
		}
		elementsInserted += groupSize;
	}
}

void PmergeMe::mergePairs(std::vector< std::vector<unsigned> > & pairs)
{
	/*
		The numbers are divided in two groups: already sorted and pending numbers
		The bigger values from the pairs are already sorted and are written into resulting vector
		The pend vector is made from the smaller values which are merged into the resulting group
	*/
	std::vector<unsigned> pend = makePend(pairs);
	std::vector<unsigned> orderingSequence = 
					makeOrderingSequence< std::vector<unsigned> >(pend.size());
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

	unsigned staggler = 0;
	if (initVct.size() % 2 == 1) {
		staggler = initLst.back();
		initLst.pop_back();
	}

	
	std::list< std::list<unsigned> > pairs;
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

void PmergeMe::makePairs(std::list< std::list<unsigned> > & pairs)
{
	std::list<unsigned> tmp;
	for (std::list<unsigned>::iterator it = initLst.begin(); it != initLst.end(); it++)
	{
		tmp.push_back(*it);
		if (tmp.size() == 2) {
			pairs.push_back(tmp);
			tmp.clear();
		}
	}
}
void PmergeMe::sortEachPair(std::list< std::list<unsigned> > & pairs)
{
	for (std::list< std::list<unsigned> >::iterator it = pairs.begin();
													it != pairs.end(); it++)
	{
		std::list<unsigned> & pair = *it;
		if (pair.front() > pair.back()) {
			std::swap(pair.front(), pair.back());
		}
	}
}

void PmergeMe::sortInsert(std::list< std::list<unsigned> > & pairs)
{
	// iterator to the next element to insert
	// and to erase it from the initial position
	std::list< std::list<unsigned> >::iterator itPos = ++(pairs.begin());
	
	// temporary iterator to preserve the end of the sorted sequence
	// after erasing the inserted element from its initial position
	std::list< std::list<unsigned> >::iterator itSorted (itPos);

	while(itPos != pairs.end()) {
		std::list<unsigned> keyToInsert = *itSorted;
		itSorted++;
		pairs.erase(itPos);
		pairs.insert(std::upper_bound(pairs.begin(), itSorted, keyToInsert, comparePairsLst), keyToInsert);
		itPos = itSorted;
	}
}

void PmergeMe::mergePairs(std::list< std::list<unsigned> > & pairs)
{
	std::list<unsigned> pend = makePend(pairs);

	std::list<unsigned> orderingSequence =
					makeOrderingSequence< std::list<unsigned> >(pend.size());

	mergePend(pend, orderingSequence);
}

void PmergeMe::mergeGroup(std::list<unsigned>::iterator pendIt, std::list<unsigned>::iterator resIt, size_t n)
{
	while (n > 0) {
		// std::cout << "Inserting a " << *pendIt << " before the " << *resIt << std::endl;
		std::list<unsigned>::iterator nextRes = resIt;
		nextRes--;
		resLst.insert(std::upper_bound(resLst.begin(), resIt, *pendIt), *pendIt);	
		resIt = nextRes;
		pendIt--;
		n--;
	}
}

void PmergeMe::mergePend(std::list<unsigned> & pend, std::list<unsigned> & orderingSequence)
{
	std::list<unsigned>::iterator it = pend.begin();
	std::list<unsigned>::iterator biggerPairIt = resLst.begin();
	biggerPairIt++;
	biggerPairIt++;

	// we move an iterator 
	// we iterate through a group backwards
	// insert each element in the range begin, according bigger element;
	// to keep track of this bigger element we can keep an iterator to it:
	// std::list preserves the iterators when inserting other elements
	for (std::list<unsigned>::iterator groupsIt = orderingSequence.begin();
									groupsIt != orderingSequence.end(); groupsIt++)
	{
		for (unsigned n = 0; n < *groupsIt - 1; n++) {
			it++;
			biggerPairIt++;
		}
		mergeGroup(it, biggerPairIt, (*groupsIt));

		it++;
		biggerPairIt++;
	}
}

std::list<unsigned> PmergeMe::makePend(std::list< std::list<unsigned> > & pairs)
{
	std::list<unsigned> pend;

	resLst.push_back(pairs.front().front());
	resLst.push_back(pairs.front().back());
	
	pairs.pop_front();
	for (std::list< std::list<unsigned> >::iterator it = pairs.begin();
							it != pairs.end(); it++)
	{
		unsigned resValue = (*it).back();
		unsigned pendValue = (*it).front();
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

void PmergeMe::checkResult() const
{
	std::vector<unsigned> checkVector(initVct);
	
	std::cout << "---------- Checking sorted containers ----------" << std::endl;
	std::cout << "std::vector: ";
	std::sort(checkVector.begin(), checkVector.end());
	
	if (checkVector == resVct) {
		std::cout << "[OK]" << std::endl;
	} else {
		std::cout << "[KO]" << std::endl;
	}
	
	std::list<unsigned> checkList(initLst);
	std::cout << "std::list: ";
	checkList.sort();
	if (checkList == resLst) {
		std::cout << "[OK]" << std::endl;
	} else {
		std::cout << "[KO]" << std::endl;
	}
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
bool PmergeMe:: comparePairsLst(const std::list<unsigned> & left, const std::list<unsigned> & right)
{
	return left.back() < right.back();
}

/*Comparison function that returns True if left < right*/
bool PmergeMe:: comparePairsVct(const std::vector<unsigned> & left, const std::vector<unsigned> & right)
{
	return left.back() < right.back();
}
