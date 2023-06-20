/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:20:59 by dselmy            #+#    #+#             */
/*   Updated: 2023/06/20 17:56:57 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef P_MERGE_ME_HPP
# define P_MERGE_ME_HPP

# include <algorithm>
# include <ctime>
# include <iostream>
# include <list>
# include <sstream>
# include <string>
# include <vector>

class PmergeMe {
public:
	PmergeMe();
	PmergeMe(const PmergeMe & rhs);
	PmergeMe & operator= (const PmergeMe & rhs);
	~PmergeMe();

	void sortVct(int argc, char ** argv);
	void sortLst(int argc, char ** argv);
	void print() const;

private:

	std::list<int>	initLst;
	std::list<int>	resLst;
	double			timeMsLst;

	std::vector<int>	initVct;
	std::vector<int>	resVct;
	double				timeMsVct;

	/* Methods for sorting using std::vector */

	void				makePairs(std::vector< std::vector<int> > & pairs);
	void				sortEachPair(std::vector< std::vector<int> > & pairs);
	void				sortInsert(std::vector< std::vector<int> > & pairs, size_t right);
	void				mergePairs(std::vector< std::vector<int> > & pairs);
	void				mergePend(std::vector<int> & pend, std::vector<int> & orderingSequence);
	std::vector<int>	makePend(std::vector< std::vector<int> > & pairs);

	/* Methods for sorting using std::list */

	void			makePairs(std::list< std::list<int> > & pairs);
	void			sortEachPair(std::list< std::list<int> > & pairs);
	void			sortInsert(std::list< std::list<int> > & pairs);
	void			mergePairs(std::list< std::list<int> > & pairs);
	void			mergePend(std::list<int> & pend, 
									std::list<int> & orderingSequence);
	std::list<int>	makePend(std::list< std::list<int> > & pairs);
	void			mergeGroup(std::list<int>::iterator pendIt, 
							std::list<int>::iterator resIt, size_t n);

	/* Helper methods */

	static bool comparePairsLst(const std::list<int> & left, const std::list<int> & right);
	static bool comparePairsVct(const std::vector<int> & left, const std::vector<int> & right);
	double makeTime(const std::clock_t & start) const;
	void putTime() const;
	
	template<typename T>
	static T makeOrderingSequence (size_t totalSize) {
		T sequence;
		
		size_t jacobstalNum = 2;
		size_t total = 0;

		while (total + jacobstalNum <= totalSize) {
			sequence.push_back(jacobstalNum);
			total += jacobstalNum;
			if (sequence.size() > 1) {
				// N-th Jacobstal number formula is:
				// Jn = Jn-1 + 2 × Jn-2
				int previous = sequence.back();
				int before_previous = *(++sequence.rbegin());
				jacobstalNum = previous + 2 * before_previous;
			}
		}
		if (total < totalSize)
			sequence.push_back(totalSize - total);
		return sequence;
	}

	template <typename T>
	void processNumbers(int argc, char ** argv, T & cont)
	{
		int number;
		for (int i = 1; i < argc; i++) {
			std::stringstream stream(argv[i]);
			stream >> number;
			while (number > 0) {
				cont.push_back(number);
				number = 0;
				stream >> number;
			}
		}
	}
};

#endif
