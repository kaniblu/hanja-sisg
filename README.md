# Hanja-aware Korean Word Representations #

This is the training code for ["Don't Just Scratch the Surface: Enhancing Word Representations for Korean with Hanja"](https://coming-soon).
The code is based on [FastText](https://github.com/facebookresearch/fasttext), with an additional functionality to take Hanja-annotated texts and perform Hanja-level skip-gram learning.

**Hanja** exists in parallel to the more commonly used **Hangul**, the Korean alphabet. Hanja shares many roots to the Chinese characters, and thus provides rich insights to the meaning of Korean words and also help to reduce ambiguity in Korean texts.

For more information about the method, please refer to our paper.

## Training from Scratch ##

Compile the source code in `cpp` directory first:

    cd cpp && make

To train a Hanja-aware Subword Information Skip-gram from the scratch, you
need to prepare two datasets:
  
  1. a Hanja-annotated Korean corpus tagged using an appropriate tool such as [hanja-tagger](https://github.com/kaniblu/hanja-tagger). The corpus must also be split into [**jamo**](https://en.wikipedia.org/wiki/List_of_Hangul_jamo), in which each empty jongsong (final consonant) must be padded with the character `e`.
  2. and Chinese character embeddings such as [Chinese word vectors](https://github.com/Embedding/Chinese-Word-Vectors) made available by Li et al.

An example line of the corpus described in (1.) is as follows.

    ㄹㅗㅅㄷㅔeㄱㅓㄴㅅㅓㄹㅇㅔe ㅍㅐe(败)ㅎㅏㄴ ㅁㅣeㅅㅓㅇㅋㅡeㄹㅗeㅂㅏe ㅈㅐeㄱㅓㄴㅊㅜㄱ(再建筑) ...

Line above was preprocessed and annotated from the original sentence `롯데건설에 패한 미성크로바 재건축 ...`.

With those two datasets ready, run `fasttext skipgram` with the following options:

    ./fasttext skipgram -minCount 10 -bucket 20000000 -minn 1 -maxn 6 -minjn 3 \\
                        -maxjn 5 -emptyjschar e -t 0.0001 -lr 0.05 -dim 300 \\
                        -ws 5 -loss ns -neg 5 -epoch 5 -thread 8 -verbose 2 \\
                        -minhn 1 -maxhn 4 -pretrainedVectors <path-to-cn-word2vec-mixedlarge-300d.txt> \\
                        -loadTarget ngrams -input <path-to-hanja-corpus> \\
                        -output <path-to-output>

Here, `minhn`, `maxhn`, `pretrainedVectors` are options specific to this work.

  * `minhn`, `maxhn`: minimum and maximum bounds for Hanja n-grams to consider for subword information skip-gram.
  * `pretrainedVectors`: n-grams embeddings to initialize from.

Unfortunately, the corpus we used to train our model can't be made available due to 
license issues. Inquire corresponding authors (kangminyoo@europa.snu.ac.kr, taeuk@europa.snu.ac.kr)
for more information on reproducibility.


## Pre-trained Models ##

We provide Hanja-SISG embeddings trained using the following datasets:

1. A comprehensive Korean corpus with a mixture of wikipedia, web-crawled news articles, and Sejong corpus
2. Chinese SGNS word2vec provided by [link](https://github.com/Embedding/Chinese-Word-Vectors) (Mixed-large / Word + Character + Ngram).

For each configuration, we make three items available: the binary model file, the word2vec file and the word2vec with
words transformed into syllables (e.g. "ㅇㅏㄴ" -> "안"). The binary model file can be
used to infer word vectors for unseen words using `fasttext` executable compiled from this repository.

| Name | Options | bin | vec | vec (syllables) |
| ---- | ------- | --- | --- | --------------- |
| `SISG(c)` | char n-gram: 1-6; jamo n-gram: 0; hanja n-gram: 0 | [link](https://drive.google.com/file/d/1RVf_T96zFoeZvtROheYw_lCDZhxlvEkE/view?usp=sharing) | [link](https://drive.google.com/file/d/1KARmGNCd5Zon8vvi8Pqxdg0K1hBZP6Y7/view?usp=sharing) | [link](https://drive.google.com/file/d/1MRdnrsEKPrwiep2Kp2EgdDJ5u7dT5ezN/view?usp=sharing) |
| `SISG(cj)` | char n-gram: 1-6; jamo n-gram: 3-5; hanja n-gram: 0 | [link](https://drive.google.com/file/d/1rCsASaysfjC6IO9M7BPR5kffTzMj5CMh/view?usp=sharing) | [link](https://drive.google.com/file/d/10AvgUdLuws5RSh8lClkTr7IkBPijxDW7/view?usp=sharing) | [link](https://drive.google.com/file/d/16wyQFJILa-8XiY6A_E3oT7vDXzhc-ggf/view?usp=sharing) |
| `SISG(cjh3)` | char n-gram: 1-6; jamo n-gram: 3-5; hanja n-gram: 1-3 | [link](https://drive.google.com/file/d/1Ch6EhGp-qmz_AoAQ065zhh37r3QV62TP/view?usp=sharing) | [link](https://drive.google.com/file/d/1xaz6KWmg-tRT7ZQKzYrlsQ0b-oAKvkJt/view?usp=sharing) | [link](https://drive.google.com/file/d/1UK8KpGN3yRKaYJ3J0qK-WWZvLJBLjPOg/view?usp=sharing) |
| `SISG(cjh4)` | char n-gram: 1-6; jamo n-gram: 3-5; hanja n-gram: 1-4 | [link](https://drive.google.com/file/d/11457297D798Ptf4Qp1hvBODCS3kcGCef/view?usp=sharing) | [link](https://drive.google.com/file/d/1plQSExbM_aZOaYkbpGRMbxzotcZscPNd/view?usp=sharing) | [link](https://drive.google.com/file/d/15mFBxTcUElZMte83asOP111kff5XRCTA/view?usp=sharing) |

## Citation ##

If you use our work, please cite the paper or the code using the following BibTex entry:

    Coming Soon

or 

    @misc{yookim2019,
      author =       {Kang Min Yoo and Taeuk Kim and Sang-goo Lee},
      title =        {Hanja-level SISG},
      howpublished = {\url{https://github.com/kaniblu/hanja-sisg}},
      year =         {2019}
    }
