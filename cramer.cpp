
#include <iostream>
 #include <math.h>
 #include <iomanip>
 #include <vector>
 #include <stdlib.h>

 /*
16
17 CRAMER'S RULE
18 1st calculate determinant of A
19 -reduce matrix recursively until it's inthe form ad-bc
20 2nd Calculate each determinant of replacing columns with results
21 -stores determinants in vector array
22 3rd Displays results
23 - dx/dA dy/dA dz/dA
24 Notes
25 can take any number of order
26 returns 0 if determinant of A is 0
27 */
 using namespace std;

 //PROTOTYPE FUNCTIONS

 //Determinant functions
 float detCalc(vector< vector<float> >&matrix, int order);
 void makeTemp (vector< vector<float> >&temp, vector< vector<float> >&matrix, int order, int element);
 void sizeVector (vector< vector<float> >&temp, int order);

 //Pring and user input functions
 void printMatrix(vector< vector<float> >&matrix, int order);
 void getMatrix(int &order);
 void getMatrix(vector< vector<float> >&matrix, int order);
 void getResult(vector<float>&result, int order);

 //calculate each determinant of matrix with replaced results
 float getDeterminants(vector< vector<float> >&matrix, vector<float>&result, int col,int order);


 //MAIN FUNCTION
 int main()
 {

 int order;
 float det;
 char elm = 'x';

 vector< vector<float> > matrix;
 vector< float > result;
 vector< float > determinants;

 cout <<"Remember to input matrix (N x N) separately from the result\n\n";
 getMatrix(order);
 getMatrix(matrix, order);

 getResult(result, order);
 cout<< "***********************\n\nThe matrix you input is:\n";

 printMatrix(matrix, order);
 cout<< "\n\nWith results: ";


 for (int i=0; i<order; i++)
 cout << result[i] << " ";
 cout<<endl<<endl;

 det = detCalc (matrix, order);
 if (det == 0)
 {
 cout<< "Determinant of A is 0\nCramer's Rule invalid.";
 return 0;
 }

 for (int i=0; i<order; i++){
 determinants.push_back(getDeterminants(matrix, result, i, order));
 }

 cout << "*******RESULTS*******"<<endl<<endl;

 for (int i=0; i<order; i++){
 cout << elm << " = " << determinants[i]/det<<endl<<endl;
 elm++;
 }


 return 0;
 }

 // gets matrix order from user
 void getMatrix(int &order)
 {
 cout << "Please enter matrix order (excluding result): ";
 cin >> order;
 }

 //gets matrix elements from user
 void getMatrix(vector< vector<float> >&matrix, int order)
 {
 cout << "\n\nEnter matrix N x N (separate with space or enter):\n";

 for(int i=0;i<order;i++) {
 //Create a vector
 vector<float> row;
 for(int j=0;j<order;++j){
 float value;
 cin >> value;
 row.push_back(value);
 }
 //Push the row in matrix
 matrix.push_back(row);
 }
 }
 //gets results from user
 void getResult(vector<float>&result, int order)
 {
 cout << "Enter the results of each row: ";
 for(int i=0;i<order;i++) {
 float value;
 cin >> value;
 result.push_back(value);
 }
 }

 //Gets determinant of x, y, z....by replacing results with each row and calculatingdeterminant
 float getDeterminants(vector< vector<float> >&matrix, vector<float>&result, int col,int order)
 {
 vector< vector<float> > temp;

 temp = matrix;

 for (int i = 0; i < order; i++){
 temp[i][col]= result[i];
 }

 return (detCalc (temp, order));
 }


 //prints any matrix given in any order
 void printMatrix(vector< vector<float> >&matrix, int order)
 {
 for(int i=0;i<order;++i) {
 for(int j=0;j<order;++j){
 cout << matrix[i][j] << " ";
 }
 cout << "\n";
 }
 cout <<endl;
 }

 /*Recursively loops down to get determinant in form ad-bc like a tree
162 and adds to the determinant*/
 float detCalc(vector< vector<float> >&matrix, int order)
 {
 vector< vector<float> > temp;
 sizeVector(temp, order-1);
 int sign = 1;
 float det = 0;



 if (order == 2) {
 return ((matrix[0][0]*matrix[1][1])-(matrix[0][1]*matrix[1][0])); //STOPRECURSIVE loop
 }

 for (int i = 0; i < order; i++)
 {

 makeTemp (temp, matrix, order-1, i); //calls makeTemp to initialize tempvector
 det += sign * matrix[0][i] * detCalc(temp, order-1); //recursively callsdetCalc
 sign *= -1; //flips sign to be added or substracted
 }

 return det; //return determinant result
 }

 /*Places correct numbers in the right place of temp vector*/
 //order is the order of the temp so originally -1 of matrix
 void makeTemp (vector< vector<float> >&temp, vector< vector<float> >&matrix, int order, int element)
 {

 for (int i = 1; i < order+1; i++){ //loop set to iterate through matrix, i=1because first row is not used
 int k = 0; //k is used to loop through temp
 for (int j = 0; j < order+1; j++){

 if ( j==element ) {

 continue; //when col element is reached it will skip
 }else{
 temp[i-1][k] = matrix[i][j]; //adds element corresponding to newtemp vector;
 k++; //adds one to k counter for col position
 }
 }
 }
 }

 //sizes vector to match copy (construct)
 void sizeVector (vector< vector<float> >&temp, int order) //"construct" like forvector
 {

 temp.resize(order);
 for(int i=0;i<order;i++)
 {
 temp[i].resize(order);
}
}
