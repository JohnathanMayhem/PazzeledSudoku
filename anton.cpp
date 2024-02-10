#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <iomanip>
#include <mutex>

using namespace std;

void read_file_in_vector (vector<string> &words, ifstream &in, mutex &m1, mutex &m2){
    while (!in.eof()){
        string s;
        m1.lock();
        if (!in.eof()){
            in>>s;
        }
        m1.unlock();
        //первым мьютексом обеспечиваем безопасное чтение, что пока слово читается потоком, никакой другой поток читать её не будет


        if (s.empty()){
            return;
        }
        else{
            m2.lock();
            words.push_back(s);
            m2.unlock();
        }
        //вторым мьютексом обеспечиваем безопасную запись в вектор строк, например если 1 слово "abc", второе 321, без мьютекса можем получить дичь a321bc или что-то подобное

    }
}

void counting_of_word(vector<string> &words, int &counter, string &word, int start, int endd, mutex &m){
    int summ=0;
    for (int i=start; i<endd; i++){
        if (words[i]==word) summ++;
    }
    if (summ!=0){
        m.lock();
        counter+=summ;
        m.unlock();
    }
    else{
        return;
    }
}

int main() {
    ifstream in("input.txt");
    mutex m_arr, m_in;
	int t;
	string word;
	in>>t>>word;
	vector <thread> threads_reading;
	vector <string> words;
	for (int i=0; i<t; i++){
        threads_reading.push_back(thread(read_file_in_vector,ref(words),ref(in),ref(m_in),ref(m_arr)));
        //если правильно понял, в базовом виде функции связанные с потоками делают копии объектов и работаюсь с ними, для передачи именно ссылок, нужно использовать std::ref
	}
    for (unsigned long i=0; i<threads_reading.size(); i++){
        threads_reading[i].join();
    }
    in.close();
    int counter=0,word_per_thread=(words.size() / t);
    vector <thread> threads_counting;
    for (int i=0; i<t; i++){
        int start,endd;
        start=i*word_per_thread;
        if (i==(t-1)){
            endd=words.size();
        }
        else{
            endd=(i+1)*word_per_thread;
        }
        threads_counting.push_back(thread(counting_of_word,ref(words),ref(counter),ref(word),start,endd,ref(m_arr)));
    }

    for (auto &th : threads_counting) th.join();
    cout<<counter;

	return 0;
}