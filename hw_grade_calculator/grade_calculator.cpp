// These headers define some of the classes and functions we need
#include <iostream>
#include <string>
#include <sstream>
#include <limits>

// ONLY MAKE CHANGES WHERE THERE IS A TODO

// These using declarations let us refer to things more simply
// e.g. instead of "std::cin" we can just write "cin"
using std::cin, std::cout, std::endl;
using std::string, std::getline;

// These methods are defined below the main function

// print instructions for inputting grades
void print_instructions();

// pretty print a summary of the grades
void print_results(double exam_average,
                   double hw_average,
                   double lw_average,
                   double reading,
                   double engagement,
                   double weighted_total,
                   char final_letter_grade);

// YOU ARE NOT EXPECTED TO UNDERSTAND THIS ONE... YET
// extract the category and score from the line
// and store the values in the provided variables
// if line := "exam 95", then category := "exam" and score := 95
// if the line is invalid, then category := "ignore"
void get_category_and_score(const string& line,
                            string* category,
                            double* score);

int main() {
    print_instructions();

    // ONLY MAKE CHANGES WHERE THERE IS A TODO

    // TODO(student): declare and initialize variables that you want
    double examTot = 0;
    double examCount = 0;
    double final_exam;
    double hwTot = 0;
    double hwCount = 0;
    double lwTot = 0;
    double lwCount = 0;
    double readingT = 0;
    double readingC = 0;
    double engT = 0;
    double engC = 0;

    string line;
    // read one line from standard input (discards the ending newline character)
    getline(cin, line);
    // read lines until an empty line is read
    while (!line.empty()) {
        string category;
        double score;
        get_category_and_score(line, &category, &score);

        // process the grade entry
        if (category == "exam") {
            // TODO(student): process exam score
            examTot = score + examTot;
            examCount++;
        } else if (category == "final-exam") {
            // TODO(student): process final score
            if (score != 0) {
                final_exam = score;
            }
            else {
                final_exam = 0;
            }
        } else if (category == "hw") {
            // TODO(student): process hw score
            hwTot = score + hwTot;
            hwCount++;
        } else if (category == "lw") {
            // TODO(student): process lw score
            // lwTot = score + lwTot;
            if (score == 1) {
                lwTot = lwTot + 100;
            }
            else {
                lwTot = lwTot + 0;
            }
            lwCount++;
        } else if (category == "reading") {
            // TODO(student): process reading score
            readingT = score + readingT;
            readingC++;
        } else if (category == "engagement") {
            // TODO(student): process engagement score
            engT = score + engT;
            engC++;
        }else {
            cout << "ignored invalid input" << endl;
        }

        // get the next line from standard input
        getline(cin, line);
    }

    // TODO(student): compute component averages
    double exam_average = 0;
    double hw_average = 0;
    double lw_average = 0;
    double reading = 0;
    double engagement = 0;
    exam_average = (examTot + final_exam)/(examCount + 1);
    if (exam_average <= final_exam) {
        exam_average = final_exam;
    }
    if (hwTot != 0.0) {
        hw_average = hwTot/hwCount;
    }
    else {
        hw_average = 0.0;
    }
    if (lwTot != 0.0) {
        lw_average = lwTot/lwCount;
    }
    else {
        lw_average = 0.0;
    }
    if (readingT != 0) {
        reading = (readingT/readingC) + 15;
        if (reading > 100) {
            reading = 100;
        }
    }
    else {
        reading = 0.0;
    }
    if (engT != 0.0) {
        engagement = (engT/engC) + 15;
        if (engagement > 100) {
            engagement = 100;
        }
    }    
    else {
        engagement = 0;
    }

    // TODO(student): compute weighted total of components
    double weighted_total = 0;
    weighted_total = (exam_average * 0.4) + (hw_average * 0.40) + (lw_average * 0.10) + (reading * 0.05) + (engagement * 0.05);
    // cout << hw_average << endl;


    // TODO(student): compute final letter grade
    char final_letter_grade = 'X';
    if  (weighted_total >= 90) {
        final_letter_grade = 'A';
    }
    else if (weighted_total >= 80) {
        final_letter_grade = 'B';
    }
    else if (weighted_total >= 70) {
        final_letter_grade = 'C';
    }
    else if (weighted_total >= 60) {
        final_letter_grade = 'D';
    }
    else {
        final_letter_grade = 'F';
    }

    print_results(
        exam_average, hw_average, lw_average, reading, engagement,
        weighted_total, final_letter_grade);
}

// These methods are already implemented for you
// You should not need to modify them

void print_instructions() {
    cout << "enter grades as <category> <score>" << endl;
    cout << "  <category> := exam | final-exam | hw | lw | reading | engagement" << endl;
    cout << "     <score> := numeric value" << endl;
    cout << "enter an empty line to end input" << endl;
}

void get_category_and_score(
    const string& line,
    string* category,
    double* score) {
    // turn the string into an input stream
    std::istringstream sin(line);

    // read the category (as string) and score (as double) from the stream
    sin >> *category;
    sin >> *score;

    if (sin.fail()) {
        // the stream is in a fail state (something went wrong)
        // clear the flags
        sin.clear();
        // clear the stream buffer (throw away whatever garbage is in there)
        sin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // signal that the line was invalid
        *category = "ignore";
    }
}

void print_results(
    double exam_average,
    double hw_average,
    double lw_average,
    double reading,
    double engagement,
    double weighted_total,
    char final_letter_grade) {
    cout << "summary:" << endl;
    cout << "      exam average: " << exam_average << endl;
    cout << "        hw average: " << hw_average << endl;
    cout << "        lw average: " << lw_average << endl;
    cout << "           reading: " << reading << endl;
    cout << "        engagement: " << engagement << endl;
    cout << "    ---------------" << endl;

    cout << "    weighted total: " << weighted_total << endl;

    cout << "final letter grade: " << final_letter_grade << endl;
}
