/* Copyright 2017 Kristofer Björnson
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
 *  @file ManyBodyContext.h
 *  @brief Many-body context.
 *
 *  @author Kristofer Björnson
 */


#ifndef COM_DAFER45_TBTK_MANY_BODY_CONTEXT
#define COM_DAFER45_TBTK_MANY_BODY_CONTEXT

#include "BitRegister.h"
#include "ExtensiveBitRegister.h"
#include "FockSpace.h"
#include "InteractionAmplitudeSet.h"

#include <memory>

namespace TBTK{

class ManyBodyContext{
public:
	/** Constructor. The ManyBodyContext assumes ownership of the
	 *  FockSpace and will destroy it at destrucion. */
	ManyBodyContext(FockSpace<BitRegister> *fockSpace);

	/** Constructor. The ManyBodyContext assumes ownership of the
	 *  FockSpace and will destroy it at destrucion. */
	ManyBodyContext(FockSpace<ExtensiveBitRegister> *fockSpace);

	/** Destructor. */
	~ManyBodyContext();

	/** Returns true if the wrapped FockState is of type BitRegister. */
	bool wrapsBitRegister();

	/** Returns true if the wrapped FockState is of type
	 *  ExtensiveBitRegister. */
	bool wrapsExtensiveBitRegister();

	/** Returns a pointer to the FockState<BitRegister> contained by the
	 *  wrapper. */
	FockSpace<BitRegister>* getFockSpaceBitRegister();

	/** Returns a pointer to the FockState<ExtensiveBitRegister> contained
	 *  by the wrapper. */
	FockSpace<ExtensiveBitRegister>* getFockSpaceExtensiveBitRegister();

	/** Add rule that restricts the Fock space. */
	void addRule(const FockStateRule::WrapperRule rule);
private:
	/** Pointer to FockSpace using BitRegsiter. */
	std::shared_ptr<FockSpace<BitRegister>> brFockSpace;

	/** Pointer to FockSpace using ExtensiveBitRegister. */
	std::shared_ptr<FockSpace<ExtensiveBitRegister>> ebrFockSpace;

	/** Rules specifying the relevant subspace. */
	std::vector<FockStateRule::WrapperRule> rules;

	/** Interaction amplitude set. */
	InteractionAmplitudeSet interactionAmplitudeSet;
};

inline bool ManyBodyContext::wrapsBitRegister(){
	if(brFockSpace.get() != NULL)
		return true;
	else
		return false;
}

inline bool ManyBodyContext::wrapsExtensiveBitRegister(){
	if(ebrFockSpace.get() != NULL)
		return true;
	else
		return false;
}

inline FockSpace<BitRegister>* ManyBodyContext::getFockSpaceBitRegister(){
	return brFockSpace.get();
}

inline FockSpace<ExtensiveBitRegister>* ManyBodyContext::getFockSpaceExtensiveBitRegister(){
	return ebrFockSpace.get();
}

inline void ManyBodyContext::addRule(const FockStateRule::WrapperRule rule){
	rules.push_back(rule);
}

};	//End of namespace TBTK

#endif