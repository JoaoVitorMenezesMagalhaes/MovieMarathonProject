#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <vector>
#include <algorithm>


using namespace std;

struct movies {
    int start_time;
    int end_time;
    int category;
};


bitset<24> reserve_movie_time(const bitset<24>& current_bitset, int start_time, int end_time) {

    bitset<24> timestamp_bitset = current_bitset;

    // Set the bits corresponding to the movie time slots to 1
    for (int i = start_time; i < end_time; i++) {
        timestamp_bitset.set(i, 1);
    }

    return timestamp_bitset;
}

bool compare_movies_by_end_time(const movies& a, const movies& b) {
    return a.end_time < b.end_time;
}

vector<movies> random_algorithm(vector<movies>& vector_movies, vector<int>& max_movies_per_cat) {
    vector<movies> selected_movies;
    bitset<24> timestamp_bitset;

    return selected_movies;
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    string filename = argv[1];
    int num_movies, num_cat;
    int max_movies_cat;
    int start_time, end_time, category;
    movies movie;
    vector<int> max_movies_per_cat;
    vector<movies> vector_movies;

    ifstream infile(filename);

    if (!infile) {
        cout << "Error opening file: " << filename << endl;
        return 1;
    }

    infile >> num_movies >> num_cat;

    for (int i = 0; i < num_cat; i++) {
        infile >> max_movies_cat;
        max_movies_per_cat.push_back(max_movies_cat);
    }

    for (int i = 0; i < num_movies; i++) {
        infile >> movie.start_time >> movie.end_time >> movie.category;
        if (movie.start_time == 24 || movie.end_time == 24) {
            movie.start_time = 0;
        }
        if (movie.start_time > movie.end_time || movie.start_time == movie.end_time) {
            continue;
        }
        vector_movies.push_back(movie);
    }

    sort(vector_movies.begin(), vector_movies.end(), compare_movies_by_end_time);

    vector<movies> selected_movies = random_algorithm(vector_movies, max_movies_per_cat);

    cout << selected_movies.size() << endl;

    for (int i = 0; i < selected_movies.size(); i++) {
        cout << selected_movies[i].start_time << " " << selected_movies[i].end_time << " " << selected_movies[i].category << endl;
    }

    infile.close();

    return 0;
}
