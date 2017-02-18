/* Copyright 2016 Kristofer Björnson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/** @package TBTKcalc
 *  @file FockStateSumRule.h
 *  @brief FockStateSumRule.
 *
 *  @author Kristofer Björnson
 */

#ifndef COM_DAFER45_TBTK_SUM_RULE
#define COM_DAFER45_TBTK_SUM_RULE

#include "FockSpace.h"
#include "FockStateRule.h"
#include "Index.h"

#include <initializer_list>
#include <vector>

namespace TBTK{
namespace FockStateRule{

class SumRule : public FockStateRule{
public:
	/** Constructor */
	SumRule(
		std::initializer_list<Index> stateIndices,
		unsigned int numParticles
	);

	/** Constructor */
	SumRule(
		std::vector<Index> stateIndices,
		unsigned int numParticles
	);

	/** Destructor. */
	virtual ~SumRule();

	/** Clone SumRule. */
	virtual SumRule* clone() const;

	/** Check whether a given FockState fullfills the rule with respect to
	 *  a particular FockSpace. */
	virtual bool isSatisfied(
		const FockSpace<BitRegister> &fockSpace,
		const FockState<BitRegister> &fockState
	) const;

	/** Check whether a given FockState fullfills the rule with respect to
	 *  a particular FockSpace. */
	virtual bool isSatisfied(
		const FockSpace<ExtensiveBitRegister> &fockSpace,
		const FockState<ExtensiveBitRegister> &fockState
	) const;

	/** Comparison operator. */
	virtual bool operator==(const FockStateRule &rhs) const;
private:
	/** Indices to sum over. */
	std::vector<Index> stateIndices;

	/** Number of particles that the states corresponding to the indices
	 *  stored in stateIndices are required to sum up to. */
	unsigned int numParticles;
};

};	//End of namespace FockStateRule
};	//End of namespace TBTK

#endif
