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
 *  @file Diagonalizer.h
 *  @brief Solves a Model using diagonalization.
 *
 *  @author Kristofer Björnson
 */

#ifndef COM_DAFER45_TBTK_SOLVER_DIAGONALIZATION
#define COM_DAFER45_TBTK_SOLVER_DIAGONALIZATION

#include "TBTK/Communicator.h"
#include "TBTK/Model.h"
#include "TBTK/Solver/Solver.h"

#include <complex>

namespace TBTK{
namespace Solver{

/** @brief Solves a Model using diagonalization.
 *
 *  Solves a given model by Diagonalizing the Hamiltonian. The eigenvalues and
 *  eigenvectors can then either be directly extracted and used to calculate
 *  custom physical quantities, or the PropertyExtractor can be used to extract
 *  common properties. Scales as \f$O(n^3)\f$ with the dimension of the Hilbert
 *  space. */
class Diagonalizer : public Solver, public Communicator{
public:
	/** Constructor */
	Diagonalizer();

	/** Destructor. */
	virtual ~Diagonalizer();

	/** Set self-consistency callback. If set to NULL or never called, the
	 *  self-consistency loop will not be run. */
	void setSelfConsistencyCallback(
		bool (*selfConsistencyCallback)(
			Diagonalizer &diagonalizer
		)
	);

	/** Set maximum number of iterations for the self-consistency loop. */
	void setMaxIterations(int maxIterations);

	/** Run calculations. Diagonalizes ones if no self-consistency callback
	 *  have been set, or otherwise multiple times until slef-consistencey
	 *  or maximum number of iterations has been reached. */
	void run();

	/** Get eigenvalues. */
	const double* getEigenValues();

	/** Get eigenvalues. Same as getEigenValues(), but with write access.
	 *  Use with causion. */
	double* getEigenValuesRW();

	/** Get eigenvectors. **/
	const std::complex<double>* getEigenVectors();

	/** Get eigenvectors. Same as getEigenVectors(), but with write access.
	 *  Use with causion. **/
	std::complex<double>* getEigenVectorsRW();

	/** Get eigenvalue. */
	const double getEigenValue(int state);

	/** Get amplitude for given eigenvector \f$n\f$ and physical index
	 * \f$x\f$: \f$\Psi_{n}(x)\f$.
	 *  @param state Eigenstate number \f$n\f$.
	 *  @param index Physical index \f$x\f$.
	 */
	const std::complex<double> getAmplitude(int state, const Index &index);
private:
	/** pointer to array containing Hamiltonian. */
	std::complex<double> *hamiltonian;

	/** Pointer to array containing eigenvalues.*/
	double *eigenValues;

	/** Pointer to array containing eigenvectors. */
	std::complex<double> *eigenVectors;

	/** Maximum number of iterations in the self-consistency loop. */
	int maxIterations;

	/** Callback function to call each time a diagonalization has been
	 *  completed. */
	bool (*selfConsistencyCallback)(
		Diagonalizer &diagonalizer
	);

	/** Allocates space for Hamiltonian etc. */
	void init();

	/** Updates Hamiltonian. */
	void update();

	/** Diagonalizes the Hamiltonian. */
	void solve();
};

inline void Diagonalizer::setSelfConsistencyCallback(
	bool (*selfConsistencyCallback)(
		Diagonalizer &diagonalizer
	)
){
	this->selfConsistencyCallback = selfConsistencyCallback;
}

inline void Diagonalizer::setMaxIterations(int maxIterations){
	this->maxIterations = maxIterations;
}

inline const double* Diagonalizer::getEigenValues(){
	return eigenValues;
}

inline double* Diagonalizer::getEigenValuesRW(){
	return eigenValues;
}

inline const std::complex<double>* Diagonalizer::getEigenVectors(){
	return eigenVectors;
}

inline std::complex<double>* Diagonalizer::getEigenVectorsRW(){
	return eigenVectors;
}

inline const std::complex<double> Diagonalizer::getAmplitude(
	int state,
	const Index &index
){
	const Model &model = getModel();
	return eigenVectors[model.getBasisSize()*state + model.getBasisIndex(index)];
}

inline const double Diagonalizer::getEigenValue(int state){
	return eigenValues[state];
}

};	//End of namespace Solver
};	//End of namespace TBTK

#endif
