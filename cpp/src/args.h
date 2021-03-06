/**
 * Copyright (c) 2016-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef FASTTEXT_ARGS_H
#define FASTTEXT_ARGS_H

#include <istream>
#include <ostream>
#include <string>
#include <vector>

namespace fasttext {

    enum class model_name : int {cbow=1, sg, sup};
    enum class loss_name : int {hs=1, ns, softmax};
    enum class load_target : int {words=0x1, ngrams=0x2, both=0x3};

    class Args {
        protected:
            std::string lossToString(loss_name);
            std::string loadTargetToString(load_target);

        public:
            Args();
            std::string input;
            std::string test;
            std::string output;
            double lr;
            int lrUpdateRate;
            int dim;
            int ws;
            int epoch;
            int minCount;
            int minCountLabel;
            int neg;
            int wordNgrams;
            loss_name loss;
            model_name model;
            int bucket;
            int minn;
            int maxn;
            int minhn;
            int maxhn;
            int minjn;
            int maxjn;
            std::string emptyjschar;
            std::string hanjaBracket;
            int thread;
            double t;
            std::string label;
            int verbose;
            std::string pretrainedVectors;
            load_target loadTarget;
            int saveOutput;

            bool qout;
            bool retrain;
            bool qnorm;
            size_t cutoff;
            size_t dsub;

            void parseArgs(const std::vector<std::string>& args);
            void printHelp();
            void printBasicHelp();
            void printDictionaryHelp();
            void printTrainingHelp();
            void printQuantizationHelp();
            void save(std::ostream&);
            void load(std::istream&);
    };

}

#endif
