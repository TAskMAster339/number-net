#include <cassert>
#include <cmath>
#include <vector>
#include <iostream>
#include "dataset.h"
#include "netWork.h"
#include <string>
#include <chrono>

#define TRAIN_IMG_PATH "./data/train-images-idx3-ubyte/train-images.idx3-ubyte"
#define TRAIN_LBL_PATH "./data/train-labels-idx1-ubyte/train-labels.idx1-ubyte"
#define TEST_IMG_PATH "./data/t10k-images-idx3-ubyte/t10k-images.idx3-ubyte"
#define TEST_LBL_PATH "./data/t10k-labels-idx1-ubyte/t10k-labels.idx1-ubyte"
#define EXAMPLES 60000

struct data_info{
    double* pixels;
    int digit;
};

data_info* PrepareData(const std::vector<std::vector<double>>& images, const std::vector<double>& labels, const data_NetWork& data_NW, int examples){
    data_info* data = new data_info[examples];
    for (int i = 0; i < examples; ++i){
        data[i].pixels = new double[data_NW.size[0]];
    }
    for (int i = 0; i < examples; ++i){
        data[i].digit = labels[i];
        for (int j = 0; j < data_NW.size[0]; ++j){
            data[i].pixels[j] = images[i][j];
        }
    }
    return data;
}
data_NetWork ReadDataNetWork(std::string path){
    data_NetWork data{};
    std::ifstream fin;
    fin.open(path);
    if (!fin.is_open()){
        std::cout << "Error reading the file " << path << std::endl;
        system("pause");
    }
    else
        std::cout << path << " loading...\n";
    std::string tmp;
    int L;
        fin >> tmp;
        if (tmp == "NetWork"){
            fin >> L;            
            data.L = L;
            data.size = new int[L];
            for (int i = 0; i < L; ++i){
                fin >> data.size[i];
            }
    }
    std::cout << path << " loading completed\n";
    fin.close();
    return data;
}

int main(){
    std::vector<std::vector<double>> images = readImages(TRAIN_IMG_PATH);
    std::vector<double> labels = readLabels(TRAIN_LBL_PATH);
    std::vector<std::vector<double>> testImages = readImages(TEST_IMG_PATH);
    std::vector<double> testLabels = readLabels(TEST_LBL_PATH);   

    NetWork NW;
    data_NetWork NW_config = ReadDataNetWork("./Config.txt");
    double right_ans = 0, right, predict, maxra = 0;
    int epoch = 0;
    bool study, repeat = true;
    std::chrono::duration<double> time;
   
    NW.Init(NW_config);
    NW.PrintConfig();

    while(repeat){
        std::cout << "STUDY? (1/0)" << std::endl;
        std::cin >> study;
        if (study) {
            int examples = EXAMPLES;
            data_info* data = PrepareData(images, labels, NW_config, examples);
            auto begin = std::chrono::steady_clock::now();
            while (right_ans / examples * 100 < 100){
                right_ans = 0;
                auto t1 = std::chrono::steady_clock::now();
                for (int i = 0; i < examples; ++i){
                    NW.SetInput(data[i].pixels);
                    right = data[i].digit;
                    predict = NW.ForwardFeed();
                    if (predict != right){
                        NW.BackPropagation(right);
                        NW.WeightsUpdater(0.15 * exp(-epoch / 20.0));
                    }
                    else
                        right_ans++;
                }
                auto t2 = std::chrono::steady_clock::now();
                time = t2 - t1;
                if (right_ans > maxra)
                    maxra = right_ans;
                std::cout << "right answers " << right_ans / examples * 100 << '\t' << "maxra: " << maxra / examples * 100 << " epoch: " << epoch << std::endl;
                epoch++;
                if (epoch == 20)
                    break;
                auto end = std::chrono::steady_clock::now();
                time = end - begin;
                std::cout << "TIME: " << time.count() / 60.0 << " min" << std::endl;
                
                NW.SaveWeights();
            }
        }
        else{
            NW.ReadWeights();
        }
        std::cout << "Test ? (1/0)\n";
        bool test_flag;
        std::cin >> test_flag;
        if (test_flag){
            int ex_tests = 10000;
            data_info* data_test;
            data_test = PrepareData(testImages, testLabels, NW_config, ex_tests);
            right_ans = 0;
            for (int i = 0; i < ex_tests; ++i){
                NW.SetInput(data_test[i].pixels);
                predict = NW.ForwardFeed();
                right = data_test[i].digit;
                if (right == predict)
                    right_ans++;
            }
            std::cout << "Right answers: " << right_ans / ex_tests * 100 << std::endl;
        }
        std::cout << "Repeat? (1/0)\n";
        std::cin >> repeat;
    }
    system("pause");
    return 0;
}
