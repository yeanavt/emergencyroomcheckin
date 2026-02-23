// =========================================================================================================
// ERmanager_commented.cpp is an example answer of part of the individual assignment, code analysis.
// Emergency Room Patient Check-In System
// Uses a singly-linked list sorted by pain level (descending)
// to simulate a priority-based ER waiting room.
// This is part of the materials for Yeana Bond's flipped classroom teaching demo (CS6604, Virginia Tech)
// =========================================================================================================

#include <iostream>   // For standard input/output (cin, cout)
#include <string>     // For std::string to store patient names

using namespace std;  // Allows use of cout, cin, string, etc. without std:: prefix



// ---- Struct: PatientInfo ----
// Represents a single patient node in the linked list.
// Each node holds the patient's first name, their pain level,
// and a pointer to the next patient in the waiting list.
struct PatientInfo
{
    string fname;           // Patient's first name
    
  
    int pain;               // Patient's pain level (1 = least, 10 = most extreme)
    PatientInfo * next;     // Pointer to the next patient node in the linked list
   // PatientInfo * prev;  // (Commented out) Would be used if this were a doubly-linked list
    
};

// ---- Class: ERmanager ----
// Manages the ER waiting room using a singly-linked list.
// Patients are inserted in sorted order by pain level (highest pain first).
class ERmanager
{
    private:
        PatientInfo * head;   // Pointer to the first (highest-priority) patient in the list
        
        
        
        // ---- Private helper: create() ----
        // Dynamically allocates a new PatientInfo node.
        // Returns a pointer to the new node, or NULL if allocation fails.
        PatientInfo * create() 
        {
            PatientInfo * newnode;       // Declare pointer for the new node
            try
            {
                newnode = new PatientInfo; // Attempt to allocate memory on the heap
            }

            catch (bad_alloc)             // Catch memory allocation failure
            {
                newnode = NULL;           // Set to NULL if allocation fails
            }

            return newnode;               // Return the new node (or NULL on failure)

        }
        
        // ---- Private helper: deallocate() ----
        // Traverses the entire linked list and frees (deletes) every node.
        // Called by the destructor to prevent memory leaks.
        void deallocate()
        {
            PatientInfo * deallo = head;    // Start at the head of the list
            PatientInfo * deallo2;          // Temporary pointer to hold the next node
            while (deallo != NULL)          // Continue until the end of the list
            {
                deallo2 = deallo->next;     // Save the next node before deleting current
                delete deallo;              // Free the current node's memory
                deallo = deallo2;           // Advance to the next node
            }
            deallo = nullptr;              // Set pointer to nullptr after cleanup (safety)

        }

    public:
        // ---- Constructor: ERmanager() ----
        // Initializes an empty waiting room.
        // Note: A temporary node is created but not linked into the list;
        // head is set to NULL indicating no patients are checked in yet.
        ERmanager()
        {
            PatientInfo * newnode = create();  // Allocate a temporary node (not used in list)
            newnode->fname = "";               // Initialize temporary node's name to empty
            newnode->pain = 0;                 // Initialize temporary node's pain to 0
            head = NULL;                       // Set head to NULL — the waiting room is empty
            
           // no patient is checked in yet
            
        }

        // ---- Destructor: ~ERmanager() ----
        // Called when an ERmanager object is destroyed.
        // Deallocates all nodes in the linked list and sets head to NULL.
        ~ ERmanager()
        {
            deallocate();       // Free all dynamically allocated patient nodes
            head = NULL;        // Set head to NULL after cleanup

        }

        // ---- Public method: check_in() ----
        // Inserts a new patient into the linked list in sorted order
        // by pain level (descending: highest pain at the front).
        // Returns true if check-in succeeds, false otherwise.
        bool check_in(string fname, int pain)

        {
            bool checkin = false;                  // Assume check-in fails by default
            PatientInfo * newnode = create();       // Allocate a new patient node
            newnode->fname = fname;                // Set the patient's first name
            newnode->pain = pain;                  // Set the patient's pain level
           // cout << endl << fname << pain << endl;    // (Debug) Print name and pain
           // cout << "In check_in bool" << endl;       // (Debug) Confirm entry into method

            // ---- Case 1: Invalid input or failed allocation ----
            // If node creation failed, or name is empty, or pain is 0, reject check-in
            if (newnode == NULL || fname == "" || pain == 0)
            {
                checkin = false;                   // Check-in fails
            }

            // ---- Case 2: Empty list (no patients yet) ----
            // If head is NULL, this is the first patient — make them the head
            else if (head == NULL)   // head -> Jack(5) -> Dummy
            {
               // cout << "in else if block" << endl;    // (Debug)
                newnode->next = head;              // newnode->next = NULL (list was empty)
                head = newnode;                    // The new patient becomes the head of the list
                checkin = true;                    // Check-in succeeds
            }

            // ---- Case 3: Non-empty list — insert in sorted position ----
            // Walk the list to find the correct position based on pain level
            else    // Jose(6) should be added before Jack(5)  
                
            {
               // cout << "head is not NULL" << endl;    // (Debug)
                cout << newnode->fname<<  " ";            // Print new patient's name
                cout << newnode->pain << endl;            // Print new patient's pain level
 
               PatientInfo * compare = head;             // Start comparing from the head

               // ---- Sub-case 3a: New patient has higher pain than current head ----
               // Insert at the front of the list (new patient becomes the new head)
               if ( pain > compare->pain)
               {
                    newnode->next = head;                 // New node points to current head
                    head = newnode;                       // New node becomes the new head
               }

               // ---- Sub-case 3b: New patient belongs somewhere after the head ----
               else 
               {
                  PatientInfo * compare2 = NULL;         // Trailing pointer (previous node)

                  // Traverse the list while current node's pain >= new patient's pain
                  // and we haven't reached the end of the list
                  while (pain <= compare->pain &&  compare->next != NULL)  
                  {
                     // cout << "In compare while" << endl;   // (Debug)
                      compare2 = compare;                // Save current as the trailing pointer
                      compare = compare->next;           // Advance to the next node
                  }
                //  cout << compare->fname << endl;      // (Debug)
                //  cout << "out of while" << endl;      // (Debug)
                    

                  // ---- Sub-case 3b-i: Found a node with lower pain ----
                  // Insert the new node between compare2 and compare
                  if (pain > compare->pain) // to ensure that compare->pain is less than newnode's pain
                  {
                      compare2->next = newnode;          // Previous node now points to new node
                      newnode->next = compare;           // New node points to the node with lower pain
                                            
                  }
                  

                  // ---- Sub-case 3b-ii: New patient has the smallest (or tied) pain ----
                  else  // to ensure that smaller pain values
                  {
                      // If we've reached the end of the list and compare's pain >= new pain,
                      // append the new node at the very end
                      if (compare->next == NULL && compare->pain >= pain) // the person with smallest value connects to null
                      {
                          newnode->next = NULL;           // New node is now the last node
                          compare->next = newnode;        // Previous last node points to new node

                      }

                      // Otherwise, insert the new node before compare but after compare2
                      else // the person with second last smallest pain level gets added before compare but after compare2 
                      {
                         newnode->next = compare;         // New node points to compare
                         compare2->next = newnode;        // Previous node points to new node
                      }
                  }

                  
               }
               
               
               compare = head;       // Reset compare pointer back to head (cleanup)
               checkin = true;       // Check-in succeeds
            
                
            }
            return checkin;           // Return whether check-in was successful

         }
        
        // ---- Friend function declaration ----
        // Allows the show() function to access private members of ERmanager
        friend void show(ERmanager & E);


};



// ---- Friend function: show() ----
// Displays all patients currently in the waiting room,
// from highest pain (front of list) to lowest pain (end of list).
void show(ERmanager & E)
{
    PatientInfo * ptr = E.head;            // Start at the head of the waiting list
      while ( ptr != NULL)                 // Traverse until end of list
      {
        // cout << " show while loop here" << endl;   // (Debug)
        cout << ptr->fname << " (" << ptr->pain << ") ->" << " ";  // Print patient name and pain
        ptr = ptr->next;                   // Move to the next patient
        
      }
     cout << "End of waiting room list for now!" << endl;  // Indicate end of the list


};

// ---- Main function ----
// Simulates an ER check-in system. Pre-loads some patients,
// then enters an interactive loop where the user can check in
// additional patients by entering their name and pain level.
int main()
{
    ERmanager * waiting_room = new ERmanager;    // Dynamically allocate an ERmanager object
    // simulate an ER waiting check in

    waiting_room->check_in("Jack", 5);          // Check in Jack with pain level 5
    show( *  waiting_room);                      // Display the current waiting list

    waiting_room->check_in("Jose", 6);          // Check in Jose with pain level 6
    show( *  waiting_room);                      // Display — Jose(6) should appear before Jack(5)

    waiting_room->check_in("Chris", 10);        // Check in Chris with pain level 10
    show( *  waiting_room);                      // Display — Chris(10) at the front

    waiting_room->check_in("Mary", 6);          // Check in Mary with pain level 6
    show( * waiting_room);                       // Display — Mary(6) inserted among same-level

    waiting_room->check_in("Jay", 2);           // Check in Jay with pain level 2
    
    show( * waiting_room);                       // Display — Jay(2) at the end

    //delete waiting_room;   --- delete after the do while loop ends, otherwise free() Aborted error again! 
    
    string fname;           // Variable to hold the user-entered patient name
    int pain;               // Variable to hold the user-entered pain level
   // int flag;             // (Commented out) Was possibly used for input validation
    do
    {
        cout << endl << endl;
        cout << "----- Welcome to check-in kiosk! -----" << endl;   // Kiosk greeting

        
        
        cout << "What is your first name? ";   // Prompt for patient's first name
        cin >> fname;                          // Read the first name from user input
     //   flag = fname.length(); /              // (Commented out) Length check
        

        cout << "What is your pain level? (from  1 = least pain --------- to 10 = most extreme pain): ";  // Prompt for pain
        cin >> pain;                           // Read the pain level from user input
        if ( pain == 0)                        // If pain is 0, no check-in needed
        {
            cout << "No pain, no check-in!" << endl;   // Inform user: 0 pain means exit
        }
        else
        {
           waiting_room->check_in(fname, pain);   // Check in the patient with given name and pain
           show( * waiting_room);                  // Display the updated waiting list
        }
            
        


    } while ( pain != 0   );                 // Loop continues until user enters pain level 0
        
    
     // pain-focused ER...no pain, no check-in!!!
    cout << "Good bye!" << endl;              // Farewell message when user exits

    delete waiting_room;                      // Deallocate the ERmanager and all patient nodes
    return 0;                                 // Program ends successfully
}
