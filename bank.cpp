#include<iostream>
#include<fstream>
using namespace std;

class Account {
    private:
        char acc_no[20], fname[10], lname[10];
        float balance;
    public:
        void read_data() {
            cout << "Enter Account Number: "; cin >> acc_no;
            cout << "Enter First Name: "; cin >> fname;
            cout << "Enter Last Name: "; cin >> lname;
            cout << "Enter Balance: "; cin >> balance;
        }
        void show_data() {
            cout << "Account Number: " << acc_no << endl;
            cout << "First Name: " << fname << endl;
            cout << "Last Name: " << lname << endl;
            cout << "Current Balance: Rs. " << balance << endl;
            cout << "-------------------------------" << endl;
        }
        void write_rec() {
            ofstream outfile("record.bank", ios::binary|ios::app);
            read_data();
            outfile.write((char*)this, sizeof(*this));
            outfile.close();
        }
        void read_rec() {
            ifstream infile("record.bank", ios::binary);
            cout << "\n****Data from file****\n";
            while(infile.read((char*)this, sizeof(*this)))
                show_data();
            infile.close();
        }
        void search_rec() {
            int n;
            ifstream infile("record.bank", ios::binary);
            infile.seekg(0,ios::end);
            int count = infile.tellg()/sizeof(*this);
            cout << "\n There are " << count << " record in the file";
            cout << "\n Enter Record Number to Search: "; cin >> n;
            infile.seekg((n-1)*sizeof(*this));
            infile.read((char*)this, sizeof(*this));
            show_data();
        }
        void edit_rec() {
            int n;
            fstream iofile("record.bank", ios::in|ios::out|ios::binary);
            iofile.seekg(0, ios::end);
            int count = iofile.tellg()/sizeof(*this);
            cout << "\n There are " << count << " record in the file";
            cout << "\n Enter Record Number to edit: "; cin >> n;
            iofile.seekg((n-1)*sizeof(*this));
            iofile.read((char*)this, sizeof(*this));
            cout << "Record " << n << " has following data\n";
            show_data();
            iofile.seekp((n-1)*sizeof(*this));
            read_data();
            iofile.write((char*)this, sizeof(*this));
        }
        void delete_rec() {
            int n;
            ifstream infile("record.bank", ios::binary);
            infile.seekg(0,ios::end);
            int count = infile.tellg()/sizeof(*this);
            cout << "\n There are " << count << " record in the file";
            cout << "\n Enter Record Number to Delete: "; cin >> n;
            fstream tmpfile("tmpfile.bank", ios::out|ios::binary);
            infile.seekg(0);
            for(int i=0; i<count; i++) {
                infile.read((char*)this,sizeof(*this));
                if(i==(n-1)) continue;
                tmpfile.write((char*)this, sizeof(*this));
            }
            infile.close();
            tmpfile.close();
            remove("record.bank");
            rename("tmpfile.bank", "record.bank");
        }
};

int main()
{
    Account A;
    int choice;
    cout<<"***Acount Information System***"<<endl;
    while(true)
    {
        cout<<"Select one option below ";
        cout<<"\n\t1-->Add record to file";
        cout<<"\n\t2-->Show record from file";
        cout<<"\n\t3-->Search Record from file";
        cout<<"\n\t4-->Update Record";
        cout<<"\n\t5-->Delete Record";
        cout<<"\n\t6-->Quit";
        cout<<"\nEnter your choice: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            A.write_rec();
            break;
        case 2:
            A.read_rec();
            break;
        case 3:
            A.search_rec();
            break;
        case 4:
            A.edit_rec();
            break;
        case 5:
            A.delete_rec();
            break;
        case 6:
            exit(0);
            break;
        default:
            cout<<"\nEnter corret choice";
            exit(0);
        }
    }
    system("pause");
    return 0;
}
