#include<iostream>
#include<fstream>
#include<string>
#include <iomanip>
#include <sstream>

using namespace std;

struct Customer{
	int items;
	int PackageNum;
	string Packaging;
	string PaymentMethod;
	string Cash;
};

Customer getData(string line)
{
	size_t pos = 0;
	size_t npos = -1;
	string delimiter = " ";
	string data[5] = {""};
	stringstream ss;
	int data_index = 0;
	Customer temp;
	int i;
	
	while((pos=line.find(delimiter))!=npos)
	{
	    data[data_index]=line.substr(0, pos);
	    line.erase(0, pos+delimiter.length());
	    data_index++;
	}

	data[data_index]=line;
	
	for (i = 0; i < 5; i++) {
		string d=*(data+i);
		if (i == 0||i == 2)
		{
			ss << d;
			if (i == 0)
			{
				ss >> temp.items;
			} else if (i == 2)
			{
				ss >> temp.PackageNum;
			}
			ss.clear();
			ss.str("");
		} else if (i == 1) {
			temp.Packaging = d;
		} else if (i == 3) {
			temp.PaymentMethod = d;
		} else if (i == 4) {
			temp.Cash = d;
		}
	}
	return temp;
}

void Infile(Customer cust, int index)
{
	double TotalDecartingTime;
	double TotalScanningTime;
	double TotalPackingTime;
	double TotalPayingTime;
	double TotalReceiptPrintingTime;
	double TotalCustomerQueueTime;
	double TotalLaneQueueTime;
	int IdleTime;
	int CustomerNumber;
	
	CustomerNumber = index+1;
	
	cout<<"Customer #"<<CustomerNumber<<"\n";
	
	cout<<"No. of Cart Items: "<<cust.items <<"\n";
	
	cout<<"Preferred Packaging: "<<cust.Packaging<<"\n";
	
	cout<<"Number of Box: "<<cust.PackageNum <<"\n";
		
		if(cust.Cash=="e")
		{
			cout<<"Preferred Payment Method: "<<cust.PaymentMethod<<" (exact) " <<"\n";
		}
		else if(cust.Cash=="ne")
		{
			cout<<"Preferred Payment Method: "<<cust.PaymentMethod<<" (not exact) "<<"\n";
		}
		else
		{
			cout<<"Preferred Payment Method: "<<cust.PaymentMethod<< "\n";
		}
	
	cout << "------------------------------\n";
		 
	TotalDecartingTime = cust.items*0.5;
	
	cout<<"Total De-Carting Time: "<<cust.items<<" * 0.5 = "<<TotalDecartingTime<<"\n";
	
	
	TotalScanningTime=cust.items*0.5;
	
	cout<<"Total Scanning Time: "<<cust.items<<" * 0.5 = "<<TotalScanningTime<<"\n";
	
		 if (cust.Packaging=="bag")
		{
			TotalPackingTime=(cust.items*0.5)+(cust.PackageNum*5);
			
			cout<<"Total Packing Time: (" <<cust.items << " * 0.5) + (" <<cust.PackageNum<<" * 5) = "<<TotalPackingTime<<"\n";
	    }
		else if(cust.Packaging=="box")
		{
			TotalPackingTime=(cust.items*0.5)+(cust.PackageNum * 10);
			
			cout<<"Total Packing Time: ("<<cust.items<<" * 0.5) + (" <<cust.PackageNum<<" * 10) = "<<TotalPackingTime<<"\n";
		}
		
		if(cust.PaymentMethod=="cash")
		{
			if(cust.Cash=="e")
			{
				TotalPayingTime=15;
				
				cout<<"Total Paying Time: "<<TotalPayingTime<<"\n";
			}
			else if(cust.Cash=="ne")
			{
				TotalPayingTime=20;
				
				cout<<"Total Paying Time: "<<TotalPayingTime<<"\n";
			}
		}
		
		if(cust.PaymentMethod=="digital")
		{
			TotalPayingTime=15;
			
			cout<<"Total Paying Time: "<<TotalPayingTime<<"\n";
		}
	
	TotalReceiptPrintingTime=(cust.items*0.3)+2;
	
	cout<<"Total Receipt Printing Time: ("<<cust.items<<" * 0.5) + 2 = "<<TotalReceiptPrintingTime<<"\n";
	
		if(index==0)
		{
			IdleTime=0;
			
			cout<<"Idle Time: "<<IdleTime<<"\n";
		}
		else if(index>0)
		{
			IdleTime = 3;
			cout<<"Idle Time: "<<IdleTime<<"\n";
		}
	
	TotalCustomerQueueTime = TotalDecartingTime + TotalScanningTime + TotalPackingTime + TotalPayingTime + TotalReceiptPrintingTime + IdleTime;
	
	cout<<"Total Customer-Queue Time: " << TotalCustomerQueueTime <<"\n";
	
	cout<<"++++++++++++++++++++++++++++++\n";

    TotalLaneQueueTime+=TotalCustomerQueueTime;
}


int main( )
{
	ifstream in_stream;
	
	in_stream.open("customer.txt");
	
		if(in_stream.fail())
	    {
	        cout<<"Input file opening failed.\n";
	        exit(1);
	    }
	    
	double TotalLaneQueueTime;
	int CustomerCount;
	int index = 0;
	string line;
	Customer n;
	
	in_stream>>CustomerCount;
	
	
	cout<<"No. of Customers:: " <<CustomerCount<<"\n";
	
	cout<<"===========================\n";
	
	
	Customer queue[CustomerCount];
		
		while(getline(in_stream, line))
		{
			if (line.length() > 0) {
				queue[index] = getData(line);
				Infile(queue[index],index);
				index++;
			}
		}

    cout<<"Total Lane Queue Time: "<<TotalLaneQueueTime;
    
	return 0;
}




















