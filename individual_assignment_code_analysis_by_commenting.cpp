// Instructor: Yeana Bond
// Course: Data Structrues and Algorithms 
// Topic: Implementing a Priority Queue Using Singly connected Linked Lists (one-way)
// Language: C++
// In-class activities: Examine this Emergency Room check-in system and share your thoughts about how this system can be improved with peers in your group.
// Assignments 
// Code analysis (Individual): Comment every line explaining what it is for and/or how it works.
// Writing assignment 1 (Individual): The individual writing assignment includes analysis of the given system prototyped in C++. You need to first run this prototype and provide two screenshot images that you ran it. 
//                                    Explain all major components of the prototype and how the current system runs relating to the course and course topic and mention flaws of the current prototype in terms of this
//                                    check-in system prioritizes patients. This write-up should be at most 2 pages using the given format. 
//                                    With your own words, you should leave a comment describing what each major component do in this file and submit it along with your write-up.
// Flipped Classroom, so my lecture focuses on the in-class discussion and at the end of the lecture, the below group assignemnts would be given to the class.  
// Improved system (Group): How can we improve this ER check-in system? Based on your in-class discussion with your peers, modify this C++ while still using singly connected linked lists. 
// Writing assignment 2 (Group report): What are the identified flaw(s) of the current check-in system that your group decided to focus and why?
//                                      What new features did your introduce to the priority queue for better check-in for the ER? 
//                                      What do you think your improved system is more ethical, fairer, or accessible?
//                                      What were the challenges in terms of decision making and reasong for your group's justifications?



#include <iostream>
#include <string>

using namespace std;



struct PatientInfo
{
    string fname;
    
  
    int pain;
    PatientInfo * next;
   // PatientInfo * prev;
    
};

class ERmanager
{
    private:
        PatientInfo * head;
        
        
        
        PatientInfo * create() 
        {
            PatientInfo * newnode;
            try
            {
                newnode = new PatientInfo;
            }

            catch (bad_alloc)
            {
                newnode = NULL;
            }

            return newnode;

        }
        
        void deallocate()
        {
            PatientInfo * deallo = head;
            PatientInfo * deallo2;
            while (deallo != NULL)
            {
                deallo2 = deallo->next;
                delete deallo;
                deallo = deallo2;
            }
            deallo = nullptr;

        }

    public:
        ERmanager()
        {
            PatientInfo * newnode = create();
            newnode->fname = "";
            newnode->pain = 0;
            head = NULL; 
            
           // no patient is checked in yet
            
        }

        ~ ERmanager()
        {
            deallocate();
            head = NULL;

        }

        bool check_in(string fname, int pain)

        {
            bool checkin = false;
            PatientInfo * newnode = create();
            newnode->fname = fname;
            newnode->pain = pain;
           // cout << endl << fname << pain << endl;
           // cout << "In check_in bool" << endl;

            if (newnode == NULL || fname == "" || pain == 0)
            {
                checkin = false;                
            }

            else if (head == NULL)   // head -> Jack(5) -> Dummy
            {
               // cout << "in else if block" << endl;
                newnode->next = head;
                head = newnode;
                checkin = true;
            }

            else    // Jose(6) should be added before Jack(5)  
                
            {
               // cout << "head is not NULL" << endl;
                cout << newnode->fname<<  " ";
                cout << newnode->pain << endl;
 
               PatientInfo * compare = head;
               if ( pain > compare->pain)
               {
                    newnode->next = head;
                    head = newnode;   
               }

               else 
               {
                  PatientInfo * compare2 = NULL;
                  while (pain <= compare->pain &&  compare->next != NULL)  
                  {
                     // cout << "In compare while" << endl;
                      compare2 = compare; // to ensure that compare2 is capturing the compare->prev
                      compare = compare->next;
                  }
                //  cout << compare->fname << endl;
                //  cout << "out of while" << endl;
                    

                  if (pain > compare->pain) // to ensure that compare->pain is less than newnode's pain
                  {
                      compare2->next = newnode;
                      newnode->next = compare;
                                            
                  }
                  

                  else  // to ensure that smaller pain values
                  {
                      if (compare->next == NULL && compare->pain >= pain) // the person with smallest value connects to null
                      {
                          newnode->next = NULL;
                          compare->next = newnode;

                      }

                      else // the person with second last smalles pain level gets added before compare but after compare2 
                      {
                         newnode->next = compare;
                         compare2->next = newnode;
                      }
                  }

                  
               }
               
               
               compare = head;
               checkin = true;
            
                
            }
            return checkin;

         }
        
        friend void show(ERmanager & E);


};



void show(ERmanager & E)
{
    PatientInfo * ptr = E.head;
      while ( ptr != NULL)
      {
        // cout << " show while loop here" << endl;  
        cout << ptr->fname << " (" << ptr->pain << ") ->" << " ";
        ptr = ptr->next; 
        
      }
     cout << "End of waiting room list for now!" << endl;


};

int main()
{
    ERmanager * waiting_room = new ERmanager;
    // simulate an ER waiting check in

    waiting_room->check_in("Jack", 5);
    show( *  waiting_room);

    waiting_room->check_in("Jose", 6);
    show( *  waiting_room);

    waiting_room->check_in("Chris", 10);
    show( *  waiting_room);

    waiting_room->check_in("Mary", 6);
    show( * waiting_room);

    waiting_room->check_in("Jay", 2);
    
    show( * waiting_room);

    //delete waiting_room;   --- delete after the do while loop ends, otherwide free() Aborted error again! 
    
    string fname;
    int pain;
   // int flag;
    do
    {
        cout << endl << endl;
        cout << "----- Welcome to check-in kiosk! -----" << endl; 

        
        
        cout << "What is your first name? ";
        cin >> fname;
     //   flag = fname.length(); /
        

        cout << "What is your pain level? (from  1 = least pain --------- to 10 = most extreme pain): ";
        cin >> pain;
        if ( pain == 0)
        {
            cout << "No pain, no check-in!" << endl;
        }
        else
        {
           waiting_room->check_in(fname, pain);
           show( * waiting_room); 
        }
            
        


    } while ( pain != 0   ); 
        
    
     // pain-focused ER...no pain, no check-in!!!
    cout << "Good bye!" << endl;

    delete waiting_room;
    return 0;
}



