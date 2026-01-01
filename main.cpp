#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cctype>
using namespace std;



class TicketOrder {
    friend ostream& operator<<(ostream& os, const TicketOrder& rhs);
    friend istream& operator>>(istream& is, TicketOrder& rhs);
    
    private:
        string productionTitle;
        char performanceDay, performanceTime;
        int adultCount, seniorCount, studentCount;
        char accessibility;
        int accessibleCount;
        string contactDetails;
        
    public:
        TicketOrder();
        TicketOrder(string productionTitle, char performanceDay, char performanceTime,
                    int adultCount, int seniorCount, int studentCount,
                    char accessibility, int accessibleCount, string contactDetails);
        TicketOrder(const TicketOrder& otherOrder);
        
        TicketOrder& operator=(const TicketOrder& otherOrder);
        
        double getTicketCost() const;
        double getDiscount() const;
        double getProcessingFee() const;
        double getTotalCost() const;
        string getPerformanceDayName() const;
        string getPerformanceTimeName() const;
        
        // basic accessor methods provided with in-line implmeentations
        // NOTE: if you change the member variable identifiers, these will break unless also changed
        string getProductionTitle() const { return productionTitle; }
        char getPerformanceDay() const { return performanceDay; }
        char getPerformanceTime() const { return performanceTime; }
        int getAdultCount() const { return adultCount; }
        int getSeniorCount() const { return seniorCount; }
        int getStudentCount() const { return studentCount; }
        char getAccessibility() const { return accessibility; }
        int getAccessibleCount() const { return accessibleCount; }
        string getContactDetails() const { return contactDetails; }
        void setProductionTitle(string value) { productionTitle = value; }
        void setPerformanceDay(char value) { performanceDay = value; }
        void setPerformanceTime(char value) { performanceTime = value; }
        void setAdultCount(int value) { adultCount = value; }
        void setSeniorCount(int value) { seniorCount = value; }
        void setStudentCount(int value) { studentCount = value; }
        void setAccessibility(char value) { accessibility = value; }
        void setAccessibleCount(int value) { accessibleCount = value; }
        void setContactDetails(string value) { contactDetails = value; }
        
}; // END class TicketOrder

ostream& operator<<(ostream& os, const TicketOrder& rhs){
    	//OUTPUT ALL VALID ORDER DETAILS
    	const double FEE_AMOUNT = 0.5;
    	
    	os << left << setw(10) << rhs.getProductionTitle();
    	os << right << setw(6) << rhs.getPerformanceDay() << setw(6) << rhs.getPerformanceTime();
    	os << setw(7) << rhs.getAdultCount() << setw(6) << rhs.getSeniorCount() << setw(7) << rhs.getStudentCount();
    	os << setw(7) << rhs.getAccessibility() << setw(6) << rhs.getAccessibleCount();
    	        
    	int totalNum = rhs.getAdultCount() + rhs.getSeniorCount() + rhs.getStudentCount();
    	double totalFees = totalNum * FEE_AMOUNT;
    	double totalPrice = rhs.getTotalCost();
    	os << " $" << setw(7) << totalPrice << endl;
    
    	return os;
}//end << overload

istream& operator>>(istream& is, TicketOrder& rhs){
    	if (!(is >> rhs.performanceDay >> rhs.performanceTime >> rhs.adultCount >> rhs.seniorCount 
            >> rhs.studentCount >> rhs.accessibility >> rhs.accessibleCount)){
        	return is;
    	}

    	is >> ws; 
    	getline(is, rhs.contactDetails);

    	return is;
};

TicketOrder::TicketOrder(){
    	this->productionTitle = "";
    	this->performanceDay = 'f';
    	this->performanceTime = 'e';
    	this->adultCount = 0;
    	this->seniorCount = 0;
    	this->studentCount = 0;
    	this->accessibility = 'n';
    	this->accessibleCount = 0;
    	this->contactDetails = "";
}//end default constructor

TicketOrder::TicketOrder(string productionTitle, char performanceDay, char performanceTime,
            int adultCount, int seniorCount, int studentCount,
            char accessibility, int accessibleCount, string contactDetails){
    	this->productionTitle = productionTitle;
    	this->performanceDay = performanceDay;
    	this->performanceTime = performanceTime;
    	this->adultCount = adultCount;
    	this->seniorCount = seniorCount;
    	this->studentCount = studentCount;
    	this->accessibility = accessibility;
    	this->accessibleCount = accessibleCount;
    	this->contactDetails = contactDetails;
}//end constructor

TicketOrder::TicketOrder(const TicketOrder& otherOrder){
    	this->productionTitle = otherOrder.getProductionTitle();
    	this->performanceDay = otherOrder.getPerformanceDay();
    	this->performanceTime = otherOrder.getPerformanceTime();
    	this->adultCount = otherOrder.getAdultCount();
    	this->seniorCount = otherOrder.getSeniorCount();
    	this->studentCount = otherOrder.getStudentCount();
    	this->accessibility = otherOrder.getAccessibility();
    	this->accessibleCount = otherOrder.getAccessibleCount();
    	this->contactDetails = otherOrder.getContactDetails();
}//end copy constructor

TicketOrder& TicketOrder::operator=(const TicketOrder& otherOrder){
    	this->productionTitle = otherOrder.getProductionTitle();
    	this->performanceDay = otherOrder.getPerformanceDay();
    	this->performanceTime = otherOrder.getPerformanceTime();
    	this->adultCount = otherOrder.getAdultCount();
    	this->seniorCount = otherOrder.getSeniorCount();
    	this->studentCount = otherOrder.getStudentCount();
    	this->accessibility = otherOrder.getAccessibility();
    	this->accessibleCount = otherOrder.getAccessibleCount();
    	this->contactDetails = otherOrder.getContactDetails();
    
    	return *this;
}

double TicketOrder::getTicketCost() const{
    	const double ADULT_E_PRICE = 34.99, SENIOR_E_PRICE = 30.99, STUDENT_E_PRICE = 24.99;
	const double ADULT_M_PRICE = 25.97, SENIOR_M_PRICE = 22.97, STUDENT_M_PRICE = 18.97;    
	double ticketPrice;
	
    	//CHECK FOR TIME OF PERFORMANCE
    	if (this->performanceTime == 'm' || this->performanceTime == 'M'){
		ticketPrice = ADULT_M_PRICE * this->adultCount + SENIOR_M_PRICE * this->seniorCount + STUDENT_M_PRICE * this->studentCount;
	} else {
		ticketPrice = ADULT_E_PRICE * this->adultCount + SENIOR_E_PRICE * this->seniorCount + STUDENT_E_PRICE * this->studentCount;
	}//end else
	
    	return ticketPrice;
}

double TicketOrder::getDiscount() const{
    	double ticketPrice = this->getTicketCost(), groupDiscount = 0;
	const int DISCOUNT_MIN = 10;
    	const double DISC_AMOUNT = 0.075;
    	int totalCount = this->adultCount + this->seniorCount + this->studentCount;
    
    	if (totalCount >= DISCOUNT_MIN){
		groupDiscount = DISC_AMOUNT * ticketPrice;
	}// end if
    
    	return groupDiscount;
}// end getDiscount

double TicketOrder::getProcessingFee() const{
    	int totalCount = this->adultCount + this->seniorCount + this->studentCount;
    	const double FEE_AMOUNT = 0.5;
    	return totalCount * FEE_AMOUNT;
}// end getProcessingFee

double TicketOrder::getTotalCost() const{
    	const double ADULT_E_PRICE = 34.99, SENIOR_E_PRICE = 30.99, STUDENT_E_PRICE = 24.99;
	const double ADULT_M_PRICE = 25.97, SENIOR_M_PRICE = 22.97, STUDENT_M_PRICE = 18.97;
    	double feeAmount = this->getProcessingFee();
    	double groupDiscount = this->getDiscount();
    	double ticketPrice = this->getTicketCost();

    	return ticketPrice - groupDiscount + feeAmount;
}

string TicketOrder::getPerformanceDayName() const{
    	if (this->performanceDay == 'f' || this->performanceDay == 'F'){
        	return "Friday";
    	} else if (this->performanceDay == 's' || this->performanceDay == 'S'){
        	return "Saturday";
    	} else {
        	return "Sunday";
    	}//end else if
}// end getPerformanceDayName

string TicketOrder::getPerformanceTimeName() const{
    	if (this->performanceTime == 'M' || this->performanceTime == 'm'){
        	return "Matinee";
    	} else {
        	return "Evening";
	}//end else if
}// end getPerformanceTimeName



//ASK FOR FILE PATH, ADD IT TO ARRAYS, AND OUTPUT EACH ORDER IN FILE WITH PRICE OR ERROR MESSAGE
bool uploadFile(string fileName, vector<TicketOrder>& ticketOrders);

//OUTPUT DETAILS OF EACH VALID ORDER FROM ALL FILES UPLOADED
void allDetails(const vector<TicketOrder>& ticketOrders);

//OUTPUT DETAILS OF EACH VALID ORDER SORTED BY DAY AND TIME OF PERFORMANCE                
void summaryByDay(const vector<TicketOrder>& ticketOrders);

//OUTPUT DETAILS OF EACH VALID ORDER SORTED BY PERFORMANCE NAME
void summaryByTitle(const vector<TicketOrder>& ticketOrders);

//CHECK AN ORDER FOR VALIDITY AND RETURN AN ERROR MESSAGE IF NECESSARY
string verifyMessage(char pDay, char pTime, int adultTickets, int seniorTickets, int studentTickets, int totalTickets, char accessibleChoice,
                     int accessibleCount, int maximumAcc);

//DISPLAY MENU AND GET USER INPUT
char displayMenu();

int main() {
	cout << "Welcome to the MCMT ticket processing system!" << endl << endl;

    	//DECLARE VECTORS AND OTHER VARIABLES FOR MAIN
    	vector<TicketOrder> ticketOrders;
    	char selection;
    	string fileName;
    	bool validInput = true;
    
    	//ASK FOR MENU INPUT AS LONG AS USER DOES NOT QUIT
    	while (validInput){
        
        	//get user input
        	selection = displayMenu();
    
        	//CHECK INPUT AND PERFORM ACTIONS BASED ON INPUT
        	if (selection == 'U' || selection == 'u'){
            		//ASK FOR FILE PATH AND CALL UPLOAD FILE
            		cout << "Please enter the name/path of the file: ";
            		cin >> fileName;
            		uploadFile(fileName, ticketOrders);
            
        	} else if (selection == 'A' || selection == 'a'){
            		//CHECK VALIDITY AND CALL ALL DETAILS
            		if (!ticketOrders.empty()){
                		allDetails(ticketOrders);
            		} else {
                		cout << "There have been no orders loaded, directing back to menu." << endl << endl;
            		}//end else
            
        	} else if (selection == 'D' || selection == 'd'){
            		//CHECK VALIDITY AND CALL SUMMARYBYDAY
            		if (!ticketOrders.empty()){
                		summaryByDay(ticketOrders);
            		} else {
                		cout << "There have been no orders loaded, directing back to menu." << endl << endl;
            		}//end else
            
        	} else if (selection == 'T' || selection == 't'){
            		//CHECK VALIDITY AND CALL SUMMARYBYTITLE
            		if (!ticketOrders.empty()){
                		summaryByTitle(ticketOrders);
            		} else {
                		cout << "There have been no orders loaded, directing back to menu." << endl << endl;
            		}//end else
            
        	} else if (selection == 'C' || selection == 'c'){
            		//CLEAR ALL ARRAYS
            		ticketOrders.clear();
            		cout << "All data has been cleared." << endl << endl;
            
        	} else if (selection == 'Q' || selection == 'q'){
            		//TERMINATE WHILE LOOP AND RETURN FROM MAIN
            		cout << "Thank you for using the program. Goodbye." << endl;
            		validInput = false;
        	} else {
            		cout << "Invalid option, please try again." << endl << endl;
        	}// end else
    	}//end while
    
    	return 0;
}// end main



char displayMenu(){
    	char userInput;
    
    	//OUTPUT MENU OPTIONS AND GET INPUT
    	cout << "(U) Upload a production ticket data file" << endl;
    	cout << "(A) display All loaded data details" << endl;
    	cout << "(D) display a summary by performance Day and time" << endl;
    	cout << "(T) display a summary by performance Title" << endl;
    	cout << "(C) Clear all loaded data" << endl;
    	cout << "(Q) Quit the program" << endl;
    	cout << "Please select an option from the menu: ";
    	cin >> userInput;
    	cin.ignore(500, '\n');
    	cout << endl;
    
    	return userInput;
}//end displayMenu



bool uploadFile(string fileName, vector<TicketOrder>& ticketOrders){
    	//DECLARE VARIABLES FOR UPLOADFILE
	char perfDay, perfTime, accSeat;
	int adultNum, seniorNum, studentNum, totalNum, maxAccessible, validLines = 0, invalidLines = 0, accSeatNum = 0;
	string line, perfName, contact;
	double totalFees;
	const double FEE_AMOUNT = 0.50;
	cout << fixed << setprecision(2);
    
    	//READ FILE INPUT
	ifstream userData(fileName);
	
	//CHECK IF FILE IS VALID
	if (userData){
	    	int numValid = 0;
	    	int numInvalid = 0;
	    
	    	//GET PERFORMANCE NAME
        	getline(userData, line);
        	if (fileName.find("Curtains", 0) != string::npos) {
            		perfName = "Curtains";
        	} else if (fileName.find("Oklahoma", 0) != string::npos) {
        		perfName = "Oklahoma";
        	} else if (fileName.find("Seussical", 0) != string::npos) {
        		perfName = "Seussical";
        	} else if (fileName.find("Urinetown", 0) != string::npos) {
        		perfName = "Urinetown";
        	} else {
        		perfName = "Other";
        	}//end else
            
        	//OUTPUT HEADERS
        	cout << setfill('-') << setw(62) << "" << setfill(' ') << endl;
    		cout << setw(perfName.length()) << left << "Show";
    		cout << right << setw(6) << "Show";
    		cout << setw(6) << "Show";
    		cout << setw(7) << "Adult";
    		cout << setw(6) << "Sen.";
    		cout << setw(7) << "Stud.";
    		cout << setw(7) << "Needs";
    		cout << setw(6) << "Acc.";
    		cout << setw(9) << "Total" << endl;
    		cout << setw(perfName.length()) << left << "Name";
    		cout << right << setw(6) << "Day";
    		cout << setw(6) << "Time";
    		cout << setw(7) << "Tix";
    		cout << setw(6) << "Tix";
    		cout << setw(7) << "Tix";
    		cout << setw(7) << "Acc?";
    		cout << setw(6) << "Tix";
    		cout << setw(9) << "Cost" << endl;
    		cout << setfill('-') << setw(62) << "" << setfill(' ') << endl;
        
        	//GET INFORMATION FOR EACH ORDER
        	TicketOrder temp;
		while (userData >> temp) {
            
            		//CALCULATE TOTAL TICKETS AND TOTAL FEE AMOUNT
            		totalNum = temp.getAdultCount() + temp.getStudentCount() + temp.getSeniorCount();
            		totalFees = totalNum * FEE_AMOUNT;
            
            		//DECLARE VARIABLES FOR WHILE LOOP
            		maxAccessible = totalNum / 2;
            		bool checkValid = false;
            		string errorMessage;
            
            		//OUTPUT ORDER DETAILS
            		cout << left << setw(perfName.length()) << perfName;
            		cout << right << setw(6) << temp.getPerformanceDay() << setw(6) << temp.getPerformanceTime();
            		cout << setw(7) << temp.getAdultCount() << setw(6) << temp.getSeniorCount() << setw(7) << temp.getStudentCount() << setw(7);
            		cout << temp.getAccessibility() << setw(6) << temp.getAccessibleCount();
            
            		//GET ERROR MESSAGE
            		errorMessage = verifyMessage(temp.getPerformanceDay(), temp.getPerformanceTime(), temp.getAdultCount(), temp.getSeniorCount(),
                                                 temp.getStudentCount(), totalNum, temp.getAccessibility(), temp.getAccessibleCount(), maxAccessible);
            		if (errorMessage.empty()){
                		checkValid = true;
            		}//end if
            
            		//CHECK IF THERE IS AN ERROR WITH THE ORDER
            		if (checkValid){
                		//OUTPUT TOTAL PRICE
                		double totalPrice = temp.getTotalCost();
                		cout << " $" << setw(7) << totalPrice << endl;
                		TicketOrder currentOrder = TicketOrder(perfName, temp.getPerformanceDay(), temp.getPerformanceTime(), temp.getAdultCount(), temp.getSeniorCount(),
                		                               temp.getStudentCount(), temp.getAccessibility(), temp.getAccessibleCount(), temp.getContactDetails());
                		ticketOrders.push_back(currentOrder);
                		validLines++;
            		} else {
                		//OUTPUT ERROR MESSAGE
                		cout << '\n' << errorMessage << endl;
                		cout << "   To fix this order, contact: " << temp.getContactDetails() << endl;
                		invalidLines++;
            		}//end else
		}//end while
    		cout << setfill('-') << setw(62) << "" << endl << endl;
	    
    	} else {
        	cout << "File cannot be opened, directing back to menu." << endl << endl;
    	}//end else
	if (validLines > 0){
    		return true;
	} else { 
		return false;
	}//end else
}//end uploadFile
                
                
                
void allDetails(const vector<TicketOrder>& ticketOrders){
        //DECLARE VARIABLES FOR ALLDETAILS
        const double FEE_AMOUNT = 0.50;            
        double totalPrice;
        
        //OUTPUT HEADERS
        cout << setfill('-') << setw(64) << "" << setfill(' ') << endl;
    	cout << setw(10) << left << "Show";
    	cout << right << setw(6) << "Show";
    	cout << setw(6) << "Show";
    	cout << setw(7) << "Adult";
    	cout << setw(6) << "Sen.";
    	cout << setw(7) << "Stud.";
    	cout << setw(7) << "Needs";
    	cout << setw(6) << "Acc.";
    	cout << setw(9) << "Total" << endl;
    	cout << setw(10) << left << "Name";
    	cout << right << setw(6) << "Day";
    	cout << setw(6) << "Time";
    	cout << setw(7) << "Tix";
    	cout << setw(6) << "Tix";
    	cout << setw(7) << "Tix";
    	cout << setw(7) << "Acc?";
    	cout << setw(6) << "Tix";
    	cout << setw(9) << "Cost" << endl;
    	cout << setfill('-') << setw(64) << "" << setfill(' ') << endl;
    	
    	//OUTPUT ALL VALID ORDER DETAILS
    	for (int i = 0; i < ticketOrders.size(); i++){
    	    	cout << ticketOrders[i];
    	}//end for
    	cout << setfill('-') << setw(64) << "" << setfill(' ') << endl << endl;
}//end allDetails
                
                
                
void summaryByDay(const vector<TicketOrder>& ticketOrders){
        //DECLARE AND INITIALIZE ALL VARIABLES FOR SUMMARYBYDAY
        const double FEE_AMOUNT = 0.50;
        int fridayAdultTickets = 0;
        int fridaySeniorTickets = 0;
        int fridayStudentTickets = 0;
        int fridayAccTickets = 0;
        double fridayRevenue = 0;
        int sundayAdultTickets = 0;
        int sundaySeniorTickets = 0;
        int sundayStudentTickets = 0;
        int sundayAccTickets = 0;
        double sundayRevenue = 0;
        int satEveAdultTickets = 0;
        int satEveSeniorTickets = 0;
        int satEveStudentTickets = 0;
        int satEveAccTickets = 0;
        double satEveRevenue = 0;
        int satMatAdultTickets = 0;
        int satMatSeniorTickets = 0;
        int satMatStudentTickets = 0;
        int satMatAccTickets = 0;
        double satMatRevenue = 0;
        
        //CHECK FOR DAY OR PERFORMANCE AND ADD VALUES TO TOTALS PER DAY
        for (int i = 0; i < ticketOrders.size(); i++){
            	if (ticketOrders[i].getPerformanceDay() == 'F' || ticketOrders[i].getPerformanceDay() == 'f'){
                	int totalNum = ticketOrders[i].getAdultCount() + ticketOrders[i].getSeniorCount() + ticketOrders[i].getStudentCount();
                	double totalFees = totalNum * FEE_AMOUNT;
                	fridayAdultTickets += ticketOrders[i].getAdultCount();
                	fridaySeniorTickets += ticketOrders[i].getSeniorCount();
                	fridayStudentTickets += ticketOrders[i].getStudentCount();
                	fridayAccTickets += ticketOrders[i].getAccessibleCount();
                	fridayRevenue += ticketOrders[i].getTotalCost(); 
           	} else if (ticketOrders[i].getPerformanceDay() == 'U' || ticketOrders[i].getPerformanceDay() == 'u'){
                	int totalNum = ticketOrders[i].getAdultCount() + ticketOrders[i].getSeniorCount() + ticketOrders[i].getStudentCount();
                	double totalFees = totalNum * FEE_AMOUNT;
                	sundayAdultTickets += ticketOrders[i].getAdultCount();
                	sundaySeniorTickets += ticketOrders[i].getSeniorCount();
                	sundayStudentTickets += ticketOrders[i].getStudentCount();
                	sundayAccTickets += ticketOrders[i].getAccessibleCount();
                	sundayRevenue += ticketOrders[i].getTotalCost();
            	} else if (ticketOrders[i].getPerformanceTime() == 'E' || ticketOrders[i].getPerformanceTime() == 'e') {
                	int totalNum = ticketOrders[i].getAdultCount() + ticketOrders[i].getSeniorCount() + ticketOrders[i].getStudentCount();
                	double totalFees = totalNum * FEE_AMOUNT;
                	satEveAdultTickets += ticketOrders[i].getAdultCount();
                	satEveSeniorTickets += ticketOrders[i].getSeniorCount();
                	satEveStudentTickets += ticketOrders[i].getStudentCount();
                	satEveAccTickets += ticketOrders[i].getAccessibleCount();
                	satEveRevenue += ticketOrders[i].getTotalCost();
            	} else {
                	int totalNum = ticketOrders[i].getAdultCount() + ticketOrders[i].getSeniorCount() + ticketOrders[i].getStudentCount();
                	double totalFees = totalNum * FEE_AMOUNT;
                	satMatAdultTickets += ticketOrders[i].getAdultCount();
                	satMatSeniorTickets += ticketOrders[i].getSeniorCount();
                	satMatStudentTickets += ticketOrders[i].getStudentCount();
                	satMatAccTickets += ticketOrders[i].getAccessibleCount();
                	satMatRevenue += ticketOrders[i].getTotalCost();
            	}//end else
        }//end for 
        
        //OUTPUT HEADERS
        cout << setfill('-') << setw(64) << "" << setfill(' ') << endl;
    	cout << setw(18) << left << "Performance";
    	cout << right << setw(7) << "Adult";
    	cout << setw(6) << "Sen.";
    	cout << setw(7) << "Stud.";
    	cout << setw(6) << "Acc.";
    	cout << setw(9) << "Revenue" << endl;
    	
    	//OUTPUT EACH DAY'S TOTALS
    	cout << left << setw(18) << "Friday Evening";
    	cout << right << setw(7) << fridayAdultTickets;
    	cout << setw(6) << fridaySeniorTickets;
    	cout << setw(7) << fridayStudentTickets;
    	cout << setw(6) << fridayAccTickets;
    	cout << " $" << setw(7) << fridayRevenue << endl;
    	
    	cout << left << setw(18) << "Saturday Matinee";
    	cout << right << setw(7) << satMatAdultTickets;
    	cout << setw(6) << satMatSeniorTickets;
    	cout << setw(7) << satMatStudentTickets;
    	cout << setw(6) << satMatAccTickets;
    	cout << " $" << setw(7) << satMatRevenue << endl;
    	
    	cout << left << setw(18) << "Saturday Evening";
    	cout << right << setw(7) << satEveAdultTickets;
    	cout << setw(6) << satEveSeniorTickets;
    	cout << setw(7) << satEveStudentTickets;
    	cout << setw(6) << satEveAccTickets;
    	cout << " $" << setw(7) << satEveRevenue << endl;
    	
    	cout << left << setw(18) << "Sunday Matinee";
    	cout << right << setw(7) << sundayAdultTickets;
    	cout << setw(6) << sundaySeniorTickets;
    	cout << setw(7) << sundayStudentTickets;
    	cout << setw(6) << sundayAccTickets;
    	cout << " $" << setw(7) << sundayRevenue << endl;
    	
        cout << setfill('-') << setw(64) << "" << setfill(' ') << endl << endl;
}//end summaryByDay
                  
                  
                  
void summaryByTitle(const vector<TicketOrder>& ticketOrders){
        //DEFINE VARIABLES FOR SUMMARYBYTITLE
        const double FEE_AMOUNT = 0.50;
	int curtAdultTickets = 0;
        int curtSeniorTickets = 0;
        int curtStudentTickets = 0;
        int curtAccTickets = 0;
        double curtRevenue = 0;
        int oklaAdultTickets = 0;
        int oklaSeniorTickets = 0;
        int oklaStudentTickets = 0;
        int oklaAccTickets = 0;
        double oklaRevenue = 0;
        int seussAdultTickets = 0;
        int seussSeniorTickets = 0;
        int seussStudentTickets = 0;
        int seussAccTickets = 0;
        double seussRevenue = 0;
        int urineAdultTickets = 0;
        int urineSeniorTickets = 0;
        int urineStudentTickets = 0;
        int urineAccTickets = 0;
        double urineRevenue = 0;
        int otherAdultTickets = 0;
        int otherSeniorTickets = 0;
        int otherStudentTickets = 0;
        int otherAccTickets = 0;
        double otherRevenue = 0;
        
        //CHECK FOR PERFORMANCE NAME AND ADD VALUES TO TOTALS PER PERFORMANCE
        for (int i = 0; i < ticketOrders.size(); i++){	

		if (ticketOrders[i].getProductionTitle().find("Curtains", 0) != string::npos){
			int totalNum = ticketOrders[i].getAdultCount() + ticketOrders[i].getSeniorCount() + ticketOrders[i].getStudentCount();
                	double totalFees = totalNum * FEE_AMOUNT;
                	curtAdultTickets += ticketOrders[i].getAdultCount();
                	curtSeniorTickets += ticketOrders[i].getSeniorCount();
                	curtStudentTickets += ticketOrders[i].getStudentCount();
                	curtAccTickets += ticketOrders[i].getAccessibleCount();
                	curtRevenue += ticketOrders[i].getTotalCost(); 
		} else if (ticketOrders[i].getProductionTitle().find("Oklahoma", 0) != string::npos){
                	int totalNum = ticketOrders[i].getAdultCount() + ticketOrders[i].getSeniorCount() + ticketOrders[i].getStudentCount();
                	double totalFees = totalNum * FEE_AMOUNT;
                	oklaAdultTickets += ticketOrders[i].getAdultCount();
                	oklaSeniorTickets += ticketOrders[i].getSeniorCount();
                	oklaStudentTickets += ticketOrders[i].getStudentCount();
                	oklaAccTickets += ticketOrders[i].getAccessibleCount();
                	oklaRevenue += ticketOrders[i].getTotalCost(); 
            	} else if (ticketOrders[i].getProductionTitle().find("Seussical", 0) != string::npos){
                	int totalNum = ticketOrders[i].getAdultCount() + ticketOrders[i].getSeniorCount() + ticketOrders[i].getStudentCount();
                	double totalFees = totalNum * FEE_AMOUNT;
                	seussAdultTickets += ticketOrders[i].getAdultCount();
                	seussSeniorTickets += ticketOrders[i].getSeniorCount();
                	seussStudentTickets += ticketOrders[i].getStudentCount();
                	seussAccTickets += ticketOrders[i].getAccessibleCount();
                	seussRevenue += ticketOrders[i].getTotalCost();
            	} else if (ticketOrders[i].getProductionTitle().find("Urinetown", 0) != string::npos) {
                	int totalNum = ticketOrders[i].getAdultCount() + ticketOrders[i].getSeniorCount() + ticketOrders[i].getStudentCount();
                	double totalFees = totalNum * FEE_AMOUNT;
                	urineAdultTickets += ticketOrders[i].getAdultCount();
                	urineSeniorTickets += ticketOrders[i].getSeniorCount();
                	urineStudentTickets += ticketOrders[i].getStudentCount();
                	urineAccTickets += ticketOrders[i].getAccessibleCount();
                	urineRevenue += ticketOrders[i].getTotalCost();
            	} else {
                	int totalNum = ticketOrders[i].getAdultCount() + ticketOrders[i].getSeniorCount() + ticketOrders[i].getStudentCount();
                	double totalFees = totalNum * FEE_AMOUNT;
                	otherAdultTickets += ticketOrders[i].getAdultCount();
                	otherSeniorTickets += ticketOrders[i].getSeniorCount();
                	otherStudentTickets += ticketOrders[i].getStudentCount();
                	otherAccTickets += ticketOrders[i].getAccessibleCount();
                	otherRevenue += ticketOrders[i].getTotalCost();
        	}//end else
        }//end for 
        
        //OUTPUT EACH PRODUCTION'S TOTALS
        cout << setfill('-') << setw(64) << "" << setfill(' ') << endl;
    	cout << setw(11) << left << "Performance";
    	cout << right << setw(7) << "Adult";
    	cout << setw(6) << "Sen.";
    	cout << setw(7) << "Stud.";
    	cout << setw(6) << "Acc.";
    	cout << setw(9) << "Revenue" << endl;
    	
	cout << left << setw(11) << "Curtains";
        cout << right << setw(7) << curtAdultTickets;
        cout << setw(6) << curtSeniorTickets;
        cout << setw(7) << curtStudentTickets;
        cout << setw(6) << curtAccTickets;
        cout << " $" << setw(7) << curtRevenue << endl;

    	cout << left << setw(11) << "Oklahoma";
    	cout << right << setw(7) << oklaAdultTickets;
    	cout << setw(6) << oklaSeniorTickets;
    	cout << setw(7) << oklaStudentTickets;
    	cout << setw(6) << oklaAccTickets;
    	cout << " $" << setw(7) << oklaRevenue << endl;
    	
    	cout << left << setw(11) << "Seussical";
    	cout << right << setw(7) << seussAdultTickets;
    	cout << setw(6) << seussSeniorTickets;
    	cout << setw(7) << seussStudentTickets;
    	cout << setw(6) << seussAccTickets;
    	cout << " $" << setw(7) << seussRevenue << endl;
    	
    	cout << left << setw(11) << "Urinetown";
    	cout << right << setw(7) << urineAdultTickets;
    	cout << setw(6) << urineSeniorTickets;
    	cout << setw(7) << urineStudentTickets;
    	cout << setw(6) << urineAccTickets;
    	cout << " $" << setw(7) << urineRevenue << endl;
    	
    	cout << left << setw(11) << "Other";
    	cout << right << setw(7) << otherAdultTickets;
    	cout << setw(6) << otherSeniorTickets;
    	cout << setw(7) << otherStudentTickets;
    	cout << setw(6) << otherAccTickets;
    	cout << " $" << setw(7) << otherRevenue << endl;
    	
        cout << setfill('-') << setw(64) << "" << setfill(' ') << endl << endl;
}//end summaryByTitle



string verifyMessage(char pDay, char pTime, int adultTickets, int seniorTickets, int studentTickets, int totalTickets, char accessibleChoice,
                     int accessibleCount, int maximumAcc){
	if (pDay != 'S' && pDay != 's' && pDay != 'F' && pDay != 'f' && pDay != 'U' && pDay != 'u'){
		return " ***ERROR*** You must enter S, s, F, f, U, or u for the day of performance";
    	}// end if
	    
    	if (pDay == 'S' || pDay == 's'){
		if (pTime != 'M' && pTime != 'm' && pTime != 'E' && pTime != 'e'){
        		return " ***ERROR*** You must enter M, m, E, or e for the time of the performance on Saturday";
    		}// end nested if
    	}//end if
	    
    	if (pDay == 'F' || pDay == 'f'){
		if (pTime != 'E' && pTime != 'e'){
        		return " ***ERROR*** There is only an Evening performance on Fridays";
    		}// end nested if
    	}//end if
	    
    	if (pDay == 'U' || pDay == 'u'){
		if (pTime != 'M' && pTime != 'm'){
        	    	return " ***ERROR*** There is only a Matinee performance on Sundays";
    		}// end nested if
	}//end if
	    
    	if (totalTickets == 0){
		return " ***ERROR*** The total number of tickets is not positive";
    	}// end if
	    
    	if (adultTickets < 0 || seniorTickets < 0 || studentTickets < 0){
		return " ***ERROR*** Any number of tickets cannot be less than zero";
    	}// end if
	    
    	if (accessibleChoice != 'y' && accessibleChoice != 'Y' && accessibleChoice != 'n' && accessibleChoice != 'N'){
		return " ***ERROR*** You must enter Y, y, N, or n for accessible seats";
    	}//end if
    
    	if (accessibleCount < 0 || accessibleCount > maximumAcc){
		return " ***ERROR*** Invalid number of accessible seats";
	}//end if

	if (accessibleChoice == 'N' || accessibleChoice == 'n'){
		if (accessibleCount != 0 ){
			return " ***ERROR*** Cannot have accessible seats if you said no to accessible seats";
		}//end nested if
	}//end if
	
	return "";
}// end verifyInput