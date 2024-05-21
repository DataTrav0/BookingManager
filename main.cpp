#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <vector>

#ifdef _WIN32
#define CLEAR_CONSOLE "cls"
#else
#define CLEAR_CONSOLE "printf \"\\033c\""
#endif


using namespace std;

string filename = "clients.txt";

void addClient();
void modifyClient();
void checkBookedTickets();
void checkClientDetails();
void saveClientsToFile(const string& filename);
void loadClientsFromFile(const string& filename);

struct Client
{
    string name;
    string address;
    string bookingType;
    string bookingAddress;
    string bookingDate;
    string arrivalTime;
    string accommodation;
    string nationality;
    string paymentType;
    string paymentDetails;
};

vector<Client> clients;

void addClient()
{
    Client newClient;

    cout << "Enter client details:" << endl;
    cout << "Name: ";
    getline(cin, newClient.name);
    cout << "Address: ";
    getline(cin, newClient.address);
    cout << "Type of booking (Hotel/Restaurant/Event): ";
    getline(cin, newClient.bookingType);
    cout << "Booking address: ";
    getline(cin, newClient.bookingAddress);
    cout << "Date of booking (YYYY-MM-DD): ";
    getline(cin, newClient.bookingDate);
    cout << "Expected arrival time (HH:MM): ";
    getline(cin, newClient.arrivalTime);
    cout << "Type of accommodation: ";
    getline(cin, newClient.accommodation);
    cout << "Nationality: ";
    getline(cin, newClient.nationality);
    cout << "Payment type (Mobile Banking/Credit Card/Cash on arrival): ";
    getline(cin, newClient.paymentType);

    if (newClient.paymentType == "Credit Card")
    {
        cout << "Enter credit card type (Visa/Mastercard): ";
        getline(cin, newClient.paymentDetails);
    }

    system(CLEAR_CONSOLE);

    cout << "Name: " << newClient.name << endl;
    cout << "Address: " << newClient.address << endl;
    cout << "Type of booking: " << newClient.bookingType << endl;
    cout << "Booking address: " << newClient.bookingAddress << endl;
    cout << "Date of booking: " << newClient.bookingDate << endl;
    cout << "Expected arrival time: " << newClient.arrivalTime << endl;
    cout << "Type of accommodation: " << newClient.accommodation << endl;
    cout << "Nationality: " << newClient.nationality << endl;
    cout << "Payment type: " << newClient.paymentType << endl;
    if (!newClient.paymentDetails.empty())
    {
        cout << "Payment details: " << newClient.paymentDetails << endl;
    }

    char confirm;
    cout << "Is the information correct? (y/n) ";
    cin >> confirm;
    cin.ignore();

    if (confirm == 'y' || confirm == 'Y')
    {
        clients.push_back(newClient);
        cout << "\033[1;32mClient has been added\033[0m" << endl;

        saveClientsToFile(filename);
    }
}

void modifyClient()
{
    if (clients.empty())
    {
        cout << "\033[1;31mNo clients found\033[0m" << endl;
        return;
    }

    cout << "Client List:" << endl;
    for (int i = 0; i < clients.size(); i++)
    {
        cout << i + 1 << ". " << clients[i].name << " (" << clients[i].bookingDate << ", " << clients[i].arrivalTime << ")" << endl;
    }

    int choice;
    cout << "Enter the client number to modify: ";
    cin >> choice;
    cin.ignore();

    if (choice < 1 || choice > clients.size())
    {
        cerr << "\033[1;31mInvalid choice\033[0m" << endl;
        return;
    }

    Client& selectedClient = clients[choice - 1];

    string newName, newAddress, newBookingType, newBookingAddress, newBookingDate, newArrivalTime, newAccommodation, newNationality, newPaymentType, newPaymentDetails;

    cout << "Enter new details for " << selectedClient.name << ":" << endl;
    cout << "Name: ";
    getline(cin, newName);
    cout << "Address: ";
    getline(cin, newAddress);
    cout << "Type of booking (Hotel/Restaurant/Event): ";
    getline(cin, newBookingType);
    cout << "Booking address: ";
    getline(cin, newBookingAddress);
    cout << "Date of booking (YYYY-MM-DD): ";
    getline(cin, newBookingDate);
    cout << "Expected arrival time (HH:MM): ";
    getline(cin, newArrivalTime);
    cout << "Type of accommodation: ";
    getline(cin, newAccommodation);
    cout << "Nationality: ";
    getline(cin, newNationality);
    cout << "Payment type (Mobile Banking/Credit Card/Cash on arrival): ";
    getline(cin, newPaymentType);

    if (newPaymentType == "Credit Card")
    {
        cout << "Enter credit card type (Visa/Mastercard): ";
        getline(cin, newPaymentDetails);
    }

    selectedClient.name = newName;
    selectedClient.address = newAddress;
    selectedClient.bookingType = newBookingType;
    selectedClient.bookingAddress = newBookingAddress;
    selectedClient.bookingDate = newBookingDate;
    selectedClient.arrivalTime = newArrivalTime;
    selectedClient.accommodation = newAccommodation;
    selectedClient.nationality = newNationality;
    selectedClient.paymentType = newPaymentType;
    selectedClient.paymentDetails = newPaymentDetails;

    cout << "\033[1;32mClient entry successfully modified\033[0m" << endl;
    saveClientsToFile(filename);
}

void checkBookedTickets()
{
    if (clients.empty())
    {
        cout << "\033[1;31mNo booked tickets found\033[0m" << endl;
        return;
    }

    cout << "Booked Tickets:" << endl;
    for (int i = 0; i < clients.size(); i++)
    {
        cout << i + 1 << ". " << clients[i].name << " (" << clients[i].bookingDate << ", " << clients[i].arrivalTime << ")" << endl;
    }
}

void saveClientsToFile(const string& filename)
{
    ofstream file(filename);
    if (file.is_open())
    {
        for (const Client& client : clients)
        {
            file << client.name << "," << client.address << "," << client.bookingType << "," << client.bookingAddress << "," << client.bookingDate << "," << client.arrivalTime << "," << client.accommodation << "," << client.nationality << "," << client.paymentType << "," << client.paymentDetails << endl;
        }
        file.close();
        cout << "\033[1;32mClient data saved to file: " << filename << "\033[0m" << endl;
    }
    else
    {
        cerr << "\033[1;31mUnable to open file: " << filename << "\033[0m" << endl;
    }
}

void checkClientDetails()
{
    if (clients.empty())
    {
        cout << "\033[1;31mNo clients found\033[0m" << endl;
        return;
    }

    cout << "Client List:" << endl;
    for (int i = 0; i < clients.size(); i++)
    {
        cout << i + 1 << ". " << clients[i].name << endl;
    }

    int choice;
    cout << "Enter the client number to check details: ";
    cin >> choice;
    cin.ignore();

    if (choice < 1 || choice > clients.size())
    {
        cerr << "\033[1;31mInvalid choice\033[0m" << endl;
        return;
    }

    Client& selectedClient = clients[choice - 1];

    cout << "\nName: " << selectedClient.name << endl;
    cout << "Address: " << selectedClient.address << endl;
    cout << "Type of booking: " << selectedClient.bookingType << endl;
    cout << "Booking address: " << selectedClient.bookingAddress << endl;
    cout << "Date of booking: " << selectedClient.bookingDate << endl;
    cout << "Expected arrival time: " << selectedClient.arrivalTime << endl;
    cout << "Type of accommodation: " << selectedClient.accommodation << endl;
    cout << "Nationality: " << selectedClient.nationality << endl;
    cout << "Payment type: " << selectedClient.paymentType << endl;
    if (!selectedClient.paymentDetails.empty())
    {
        cout << "Payment details: " << selectedClient.paymentDetails << endl;
    }
}


void loadClientsFromFile(const string& filename)
{
    ifstream file(filename);
    if (file.is_open())
    {
        clients.clear();
        string line;
        while (getline(file, line))
        {
            Client client;
            size_t pos = 0;
            size_t prevPos = 0;
            int fieldIndex = 0;
            while ((pos = line.find(',', prevPos)) != string::npos)
            {
                switch (fieldIndex)
                {
                case 0:
                    client.name = line.substr(prevPos, pos - prevPos);
                    break;
                case 1:
                    client.address = line.substr(prevPos, pos - prevPos);
                    break;
                case 2:
                    client.bookingType = line.substr(prevPos, pos - prevPos);
                    break;
                case 3:
                    client.bookingAddress = line.substr(prevPos, pos - prevPos);
                    break;
                case 4:
                    client.bookingDate = line.substr(prevPos, pos - prevPos);
                    break;
                case 5:
                    client.arrivalTime = line.substr(prevPos, pos - prevPos);
                    break;
                case 6:
                    client.accommodation = line.substr(prevPos, pos - prevPos);
                    break;
                case 7:
                    client.nationality = line.substr(prevPos, pos - prevPos);
                    break;
                case 8:
                    client.paymentType = line.substr(prevPos, pos - prevPos);
                    break;
                case 9:
                    client.paymentDetails = line.substr(prevPos, pos - prevPos);
                    break;
                }
                prevPos = pos + 1;
                fieldIndex++;
            }
            clients.push_back(client);
        }
        file.close();
        cout << "\033[1;32mClient data loaded from file: " << filename << "\033[0m" << endl;
    }
    else
    {
        cerr << "\033[1;31mUnable to open file: " << filename << "\033[0m" << endl;
    }
}

int main()
{
    int choice;

    loadClientsFromFile(filename);

    do
    {
        cout << "Ticket Management System" << endl;
        cout << "1. Add new client" << endl;
        cout << "2. Modify client entry" << endl;
        cout << "3. Check booked tickets" << endl;
        cout << "4. Check client details" << endl;
        cout << "5. Save clients to file" << endl;
        cout << "6. Load clients from file" << endl;
        cout << "7. Quit" << endl;
        cout << endl << "Enter your choice: ";

        cin >> choice;
        cin.ignore();

        system(CLEAR_CONSOLE);
        switch (choice)
        {
        case 1:
            addClient();
            break;
        case 2:
            modifyClient();
            break;
        case 3:
            checkBookedTickets();
            break;
        case 4:
            checkClientDetails();
            break;

        case 5:
            saveClientsToFile(filename);
            break;
        case 6:
            loadClientsFromFile(filename);
            break;
        case 7:
            cout << "\033[1;32mExiting...\033[0m" << endl;
            break;
        default:
            cout << "\033[1;31mInvalid choice\033[0m" << endl;
        }
        cout << endl;
    }
    while (choice != 7);

    return 0;
}
