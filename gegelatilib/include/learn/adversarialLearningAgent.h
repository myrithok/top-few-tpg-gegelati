/**
 * Copyright or © or Copr. IETR/INSA - Rennes (2019 - 2020) :
 *
 * Karol Desnos <kdesnos@insa-rennes.fr> (2019 - 2020)
 * Nicolas Sourbier <nsourbie@insa-rennes.fr> (2019 - 2020)
 * Pierre-Yves Le Rolland-Raumer <plerolla@insa-rennes.fr> (2020)
 *
 * GEGELATI is an open-source reinforcement learning framework for training
 * artificial intelligence based on Tangled Program Graphs (TPGs).
 *
 * This software is governed by the CeCILL-C license under French law and
 * abiding by the rules of distribution of free software. You can use,
 * modify and/ or redistribute the software under the terms of the CeCILL-C
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info".
 *
 * As a counterpart to the access to the source code and rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty and the software's author, the holder of the
 * economic rights, and the successive licensors have only limited
 * liability.
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading, using, modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean that it is complicated to manipulate, and that also
 * therefore means that it is reserved for developers and experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or
 * data to be ensured and, more generally, to use and operate it in the
 * same conditions as regards security.
 *
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL-C license and that you accept its terms.
 */


#ifndef ADVERSARIALLEARNINGAGENT_H
#define ADVERSARIALLEARNINGAGENT_H

#include "learn/adversarialEvaluationResult.h"
#include "learn/parallelLearningAgent.h"

namespace Learn{
    /**
    * \brief Class used to control the learning steps of a TPGGraph within
    * a given LearningEnvironment, with a support of adversarial allowing
    * multi-agent simulations. To have several agents per evaluation, we use a
    * job object embedding some TPG roots.
    */
    class AdversarialLearningAgent : public ParallelLearningAgent{
    protected:
        /**
         * \brief Number of agents per evaluation (e.g. 2 in tic-tac-toe).
         */
        size_t agentsPerEvaluation;

        /**
        * \brief Number of game iterations for each job evaluation.
        *
        * Each of the roots will be evaluated in several jobs, but in order to
        * have a representative score for each job, some environments will need
        * to do several iterations to make an average score.
        */
        size_t iterationsPerJob;

        /**
        * \brief Method for evaluating all roots with parallelism & adversarial.
        *
        * \param[in] generationNumber the integer number of the current
        * generation. \param[in] mode the LearningMode to use during the policy
        * evaluation. \param[in] results Map to store the resulting score of
        * evaluated roots.
        */
        void evaluateAllRootsInParallel(
                uint64_t generationNumber, LearningMode mode,
                std::multimap<std::shared_ptr<EvaluationResult>,
                        const TPG::TPGVertex*>& results) override;


    public:

        /**
        * \brief Constructor for AdversarialLearningAgent.
        *
        * Based on default constructor of ParallelLearningAgent
        *
        * \param[in] le The LearningEnvironment for the TPG.
        * \param[in] iSet Set of Instruction used to compose Programs in the
        *            learning process.
        * \param[in] p The LearningParameters for the LearningAgent.
        * \param[in] agentsPerEval The number of agents each simulation will
        * need.
        * \param[in] iterPerJob The numver of iterations per job evaluation.
        */
        AdversarialLearningAgent(LearningEnvironment& le,
                                  const Instructions::Set& iSet,
                                  const LearningParameters& p, size_t agentsPerEval=2,
                                  size_t iterPerJob=10):
                                  ParallelLearningAgent(le, iSet,p),
                                  agentsPerEvaluation(agentsPerEval),
                                  iterationsPerJob(iterPerJob)
        {
        }

        /**
        * \brief Evaluates policy starting from the given root, taking
        * adversarial in charge.
        *
        * The policy, that is, the TPGGraph execution starting from the given
        * TPGVertex is evaluated nbIteration times. The generationNumber is
        * combined with the current iteration number to generate a set of
        * seeds for evaluating the policy.
        *
        * The method is const to enable potential parallel calls to it.
        *
        * \param[in] tee The TPGExecutionEngine to use.
        * \param[in] job the TPGVertex group from which the policy evaluation
        * starts. Each of the roots of the group shall be an agent of the
        * same simulation.
        *
        * \param[in] generationNumber the integer number of the current
        * generation. \param[in] mode the LearningMode to use during the policy
        * evaluation. \param[in] le Reference to the LearningEnvironment to use
        * during the policy evaluation (may be different from the attribute of
        * the class in child LearningAgentClass).
        *
        * \return a std::shared_ptr to the EvaluationResult for the root. This
        * will be an AdversarialEvaluationResult that contains the score of
        * each root of the job. The same root can appear in several jobs, so
        * these scores are to be combined by the element that calls this
        * method.
        * AdversarialEvaluationResult will also contain the number of
        * iterations that have been done in this job, that could be useful to
        * combine results later.
        */
        virtual std::shared_ptr<EvaluationResult> evaluateJob(
                TPG::TPGExecutionEngine& tee, const Job& job,
                uint64_t generationNumber, LearningMode mode,
                LearningEnvironment& le) const override;

        /**
        * \brief Puts all roots into jobs to be able to use them in simulation
        * later. The difference with the base learning agent makeJobs is that
        * here we make jobs containing several random roots to play together.
        *
        * \param[in] mode the mode of the training, determining for exemple
        * if we generate values that we only need for training.
        * \param[in] tpgGraph The TPG graph from which we will take the
        * roots.
        *
        * @return A vector containing pointers of the newly created jobs.
        */
        std::queue<std::shared_ptr<Learn::Job>> makeJobs(Learn::LearningMode mode, TPG::TPGGraph* tpgGraph=nullptr) override;

    };
}


#endif
