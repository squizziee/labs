#include <iostream>
#include <fstream>
#include <string>
#include <io.h>
#include <sys/stat.h>

int publicLength = 0;
class Worker {
public:
    char name[16];
    char surname[16];
    char middleName[16];
    int number;
    int hoursPerMonth;
    double hourlyRate;
    union {
        double salary;
        double bigSalary;
    };
};

long GetFileSize(std::string filename) {
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

void deleteWorker(int n) {
    Worker temp1;
    Worker temp2;
    FILE* file;
    file = fopen("task3.dat", "r+");
    long long fileSize = GetFileSize("task3.dat");
    long offset = ((n - 1) * sizeof(Worker));
    while (offset < fileSize) {
        fseek(file, offset, SEEK_SET);
        fread((void*)&temp1, sizeof(Worker), 1, file);

        offset += sizeof(Worker);

        fseek(file, offset, SEEK_SET);
        fread((void*)&temp2, sizeof(Worker), 1, file);

        fseek(file, offset, SEEK_SET);
        fwrite((void*)&temp1, sizeof(Worker), 1, file);
        offset -= sizeof(Worker);
        fseek(file, offset, SEEK_SET);
        fwrite((void*)&temp2, sizeof(Worker), 1, file);

        offset += sizeof(Worker);
    }
    int success = _chsize(_fileno(file), fileSize - sizeof(Worker));
}

void editWorker(int fieldID, int index, std::string newValue) {
    Worker temp;
    FILE* file;
    file = fopen("task3.dat", "r+");
    fseek(file, (index - 1) * sizeof(Worker), SEEK_SET);
    fread(&temp, sizeof(Worker), 1, file);
    switch (fieldID) {
    case(1):
        strcpy(temp.surname, newValue.c_str());
        break;
    case(2):
        strcpy(temp.name, newValue.c_str());
        break;
    case(3):
        strcpy(temp.middleName, newValue.c_str());
        break;
    case(4):
        temp.number = std::stoi(newValue);
        break;
    case(5):
        temp.hoursPerMonth = std::stoi(newValue);
        break;
    case(6):
        temp.hoursPerMonth = std::stod(newValue);
        break;
    }
    fseek(file, (index - 1) * sizeof(Worker), SEEK_SET);
    fwrite(&temp, sizeof(Worker), 1, file);
    fclose(file);
}

int countStructs()
{
    FILE* file;
    int i = 0;
    file = fopen("task3.dat", "r");
    while (true) {
        if (fseek(file, -i * sizeof(Worker), SEEK_END) != -1) {
            i++;
        }
        else {
            break;
        }
    }
    fclose(file);
    return i - 1;

}
int addWorker(Worker obj, int amount)
{
    FILE* f;
    f = fopen("task3.dat", "a+");
    fwrite(&obj, sizeof(Worker), 1, f);
    fclose(f);
    amount++;
    return amount;
}


Worker findMyWorker(int n) {
    Worker worker;
    FILE* file;
    file = fopen("task3.dat", "r");
    fseek(file, (n - 1) * sizeof(Worker), SEEK_SET);
    fread(&worker, sizeof(Worker), 1, file);
    fclose(file);
    return worker;
}

void viewClasses() {
    Worker Worker;
    std::cout << "#" << '\t' << "surname" << '\t' << "name" << '\t' << "middleName" << '\t' << "number" << '\t' << "hoursPerMonth" << '\t' << "hourlyRate" << '\n';
    int n = countStructs();
    for (int i = 1; i <= n; ++i) {
        Worker = findMyWorker(i);
        std::cout << i << ")\t" << Worker.surname << '\t' << Worker.name << '\t' << Worker.middleName << '\t' << '\t' << Worker.number << '\t' << Worker.hoursPerMonth << '\t' << '\t' << Worker.hourlyRate << '\n';
    }
}

Worker init(Worker obj) {
    std::cout << "Surname: \n";
    std::cin >> obj.surname;
    std::cout << "Name: \n";
    std::cin >> obj.name;
    std::cout << "MiddleName: \n";
    std::cin >> obj.middleName;
    std::cout << "Number: \n";
    std::cin >> obj.number;
    std::cout << "Hours per month: \n";
    std::cin >> obj.hoursPerMonth;
    std::cout << "Hourly rate: \n";
    std::cin >> obj.hourlyRate;
    std::cout << '\n';
    return obj;
}
double calculateSalary(int hoursPerMonth, double hourlyRate) {
    double salary;
    if (hoursPerMonth > 144) {
        salary = hoursPerMonth * hourlyRate;
    }
    else {
        int overtimeHours = hoursPerMonth - 144;
        salary = (overtimeHours * hourlyRate * 2) + (144 * hourlyRate);
    }
    salary = salary * 0.88;
    return salary;
}

void enteringSalary() {
    std::ofstream out;
    out.open("task33");
    Worker pack;
    double temp;
    FILE* f;
    f = fopen("task3.dat", "r+");
    for (int i = 0; i < publicLength; ++i) {
        fseek(f, i * sizeof(Worker), SEEK_SET);
        fread(&pack, sizeof(Worker), 1, f);
        temp = calculateSalary(pack.hoursPerMonth, pack.hourlyRate);
        out << pack.name << '\t ' << temp << '\n';
        fwrite(&pack, sizeof(Worker), 1, f);
        fclose(f);
    }

}

int main() {
	Worker Worker{};
	publicLength = countStructs();
	while (!!!0) {
		std::cout << "1.Add a structure\n"
			"2.Delete a structure\n"
			"3.Change a structures\n"
			"4.Print structures\n"
			"5.Solving the problem\n"
			"6.Exit\n";
		int e;
		std::cin >> e;
		if (e == 1) {
			Worker = init(Worker);
			addWorker(Worker, publicLength);
			publicLength++;
			break;
		}
		else if (e == 2) {
			std::cout << "Enter the number of the item you want to delete:";
			int y;
			std::cin >> y;
			deleteWorker(y);
		}
		else if (e == 3) {
			int h;
			std::cout << "What structure do you want to change?\n";
			std::cin >> h;
			std::cout << "1.Surname\n" << "2.Name\n" << "3.Middle name\n" << "4.Number\n"
				<< "5.HoursPerMonth\n" <<
				"6.HourlyRate\n";
			std::cout << "Which parameter do you want to change?\n";
			int o;
			std::cin >> o;
			std::cout << "Enter the value:\n";
			std::string str;
			std::cin >> str;
			editWorker(o, h, str);
		}
        else if (e == 4) {
            viewClasses();
        }
        else if (e == 5) {
            enteringSalary();
        }
        else if (e == 6) {
            exit(0);
        }
        else {
            std::cout << "Wrong input, try again: ";
        }
	}
	return 0;
}