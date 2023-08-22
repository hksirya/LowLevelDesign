Before : 

// Class definition
class DRY {
public:
    // Method 1
    // For cse department
    void CSE() {
        cout << "This is computer science" << endl;
    }

    // Method 2
    // For cse dept. college
    void college() {
        cout << "IIT - Madras" << endl;
    }

    // Method 3
    // ece dept method
    void ECE() {
        cout << "This is electronics" << endl;
    }

    // Method 4
    // For ece dept college 1
    void college1() {
        cout << "IIT - Madras" << endl;
    }

    // Method 5
    // For IT dept
    void IT() {
        cout << "This is Information Technology" << endl;
    }

    // Method 6
    // For IT dept college 2
    void college2() {
        cout << "IIT - Madras" << endl;
    }
};

// Main driver function
int main() {
    // Creating object of class in main() function
    DRY s;

    // Calling above methods one by one
    // as created above
    s.CSE();
    s.college();
    s.ECE();
    s.college1();
    s.IT();
    s.college2();

    return 0;
}

After : 

// Main class
class DRY {
  public:
	// Method 1
	// For cse department
  void CSE()
	{

		// Print statement
		cout<<"This is computer science";

		// Calling method
		college();
	}

	// Method 2
	// For ece dept method
	 void ECE()
	{
		cout<<"This is electronics";

		// Calling method
		college();
	}

	// Method 3
	// For IT dept
	 void IT()
	{

		// Print statement
			cout<<"This is Information Technology";

		// Calling method
		college();
	}

	// Method 4
	// For college dept
	 void college()
	{

		// Print statement
		cout<<"IIT - Madras";
	}
};

	// Method 5
	// Main driver method
	int main()
	{

		// Creating object of class in main() method
		DRY s = new DRY();

		// Calling the methods one by one
		// as created above
		s.CSE();
		s.ECE();
		s.IT();
	}
}

