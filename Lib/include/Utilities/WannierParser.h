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
 *  @file WannierParser.h
 *  @brief Parses Wannier files.
 *
 *  @author Kristofer Björnson
 */

#ifndef COM_DAFER45_TBTK_WANNIER_PARSER
#define COM_DAFER45_TBTK_WANNIER_PARSER

#include "Model.h"
#include "ParallelepipedArrayState.h"
#include "ReciprocalLattice.h"

#include <string>
#include <vector>

namespace TBTK{

class WannierParser{
public:
	/** Parse file. */
	UnitCell* parseMatrixElements(std::string filename);

	/** Parse Wannier functions. */
	std::vector<ParallelepipedArrayState*> parseWannierFunctions(std::string filename);

	/** Get reciprocal lattice. */
	ReciprocalLattice* getReciprocalLattice();

	/** Get matrix dimension. */
//	unsigned int getMatrixDimension() const;
private:
	/** Reciprocal lattice. */
//	ReciprocalLattice *reciprocalLattice;

	/** Matrix dimension. */
//	unsigned int matrixDimension;
};

/*inline ReciprocalLattice* WannierParser::getReciprocalLattice(){
	return reciprocalLattice;
}*/

/*inline unsigned int WannierParser::getMatrixDimension() const{
	return matrixDimension;
}*/

};	//End of namespace TBTK

#endif
