//analysis.cpp
#include <numeric>
#include <algorithm>

#include "Student_info.h"
#include "grade.h"
#include "median.h"

bool did_all_hw(const Student_info& s) {
	return ((find(s.homework.begin(), s.homework.end(), 0)) == s.homework.end());
}//did_all_hw

double grade_aux(const Student_info& s) {
	try {
		return grade(s);
	}
	catch (domain_error) {
		return grade(s.midterm, s.final, 0);
	}
}//grade_aux

double median_analysis(const vector<Student_info>& students) {
	vector<double>grades;
	transform(students.begin(), students.end(), back_inserter(grades), grade_aux);
	return median(grades);
}//median_analysis

double optimistic_median(const Student_info& s) {
	vector<double> nonzero;
	remove_copy(s.homework.begin(), s.homework.end(), back_inserter(nonzero), 0);

	if (nonzero.empty())
		return grade(s.midterm, s.final, 0);
	else
		return grade(s.midterm, s.final, median(nonzero));
}//optimistic_median()

double optimistic_median_analysis(const vector<Student_info>& students) {
	vector<double> grades;

	transform(students.begin(), students.end(),
		back_inserter(grades), optimistic_median);

	return median(grades);
}//optimistic_median_analysis()

double average(const vector<double>& v) {
	return accumulate(v.begin(), v.end(), 0.0) / v.size();
}//average()

double average_grade(const Student_info& s) {
	return grade(s.midterm, s.final, average(s.homework));
} //average_grade()

double average_analysis(const vector<Student_info>& students) {
	vector <double> grades;
	transform(students.begin(), students.end(), back_inserter(grades), average_grade);
	return median(grades);
} //average_analysis()

void write_analysis(ostream& out, const string& name,
	double analysis(const vector<Student_info>&),
	const vector <Student_info>& did,
	const vector<Student_info> &didnt)
{
	out << name << ": median(did) = " << analysis(did)
		<< ", median(didnt) = " << analysis(didnt) << endl;
}//write_analysis()