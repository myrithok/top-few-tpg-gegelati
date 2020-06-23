/**
 * Copyright or © or Copr. IETR/INSA - Rennes (2019 - 2020) :
 *
 * Karol Desnos <kdesnos@insa-rennes.fr> (2019 - 2020)
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

#include <gtest/gtest.h>
#include <fstream>

#include "log/Logger.h"

TEST(loggerTest, Constructor) {
    ASSERT_NO_THROW(Logger l);
    ASSERT_NO_THROW(Logger l(std::cerr));
}

TEST(loggerTest, log) {
    Logger l;
    ASSERT_NO_THROW(l<<"test1"<<"test2"<<std::endl);
    std::stringstream strStr;

    Logger l2(strStr);
    ASSERT_NO_THROW(l2<<"test3"<<"test4"<<std::endl);
    ASSERT_EQ("test3test4\n",strStr.str());

    l2<<std::endl;
    ASSERT_EQ("test3test4\n\n",strStr.str());
}

TEST(loggerTest, logWithFile) {
    std::ofstream o("tempFileForTest", std::ofstream::out);
    auto l2 = Logger(o);
    l2<<"randomDataForTest0";
    o.close();

    std::ifstream i("tempFileForTest", std::ofstream::in);
    std::string s;
    i>>s;
    ASSERT_EQ("randomDataForTest0",s);

    remove("tempFileForTest");
}