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

// checar categorias

// checar se o horario está disponivel para assistir (usar bitset)

bitset<24> reserve_movie_time(const bitset<24>& current_bitset, int start_time, int end_time) {
    // Create a new bitset as a copy of the current one
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

    bitset<24> timestamp_bitset;

    // Reserve time slots for each movie in vector_movies
    for (const auto& movie : vector_movies) {
        // Check if there is enough capacity in the category of the movie
        int category_count = count_if(vector_movies.begin(), vector_movies.end(),
            [&movie](const movies& m) { return m.category == movie.category; });

        if (category_count > max_movies_per_cat[movie.category]) {
            continue;
        }

        // Check if the time slot is available
        if ((timestamp_bitset & (reserve_movie_time(bitset<24>(), movie.start_time, movie.end_time))).any()) {
            continue;
        }

        // If all checks pass, reserve the time slots for the movie and add it to the count for its category
        timestamp_bitset = reserve_movie_time(timestamp_bitset, movie.start_time, movie.end_time);
        max_movies_per_cat[movie.category]++;
    }


    infile.close();

    return 0;
}
