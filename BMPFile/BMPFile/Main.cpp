#include<fstream>
#include "HexTranslator.h"
using namespace std;

int main (int * argc, char **argv)
{
   /* Grab a file of written text 
	* Read the text in four characters
	* Add BMP header and then add text in hex
	*/
	string fileLocation;
	unsigned char bmpFileHeader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
	unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
	unsigned char bmppad[3] = {0,0,0};
	int w, h;
	w = h = 400;
	int fileSize = 54 + 3 * w * h;
	unsigned char *img = (unsigned char *)malloc(3*w*h);
	memset(img,0,sizeof(img));
	bmpFileHeader[ 2] = (unsigned char)(fileSize    );
	bmpFileHeader[ 3] = (unsigned char)(fileSize>> 8);
	bmpFileHeader[ 4] = (unsigned char)(fileSize>>16);
	bmpFileHeader[ 5] = (unsigned char)(fileSize>>24);

	bmpinfoheader[ 4] = (unsigned char)(       w    );
	bmpinfoheader[ 5] = (unsigned char)(       w>> 8);
	bmpinfoheader[ 6] = (unsigned char)(       w>>16);
	bmpinfoheader[ 7] = (unsigned char)(       w>>24);
	bmpinfoheader[ 8] = (unsigned char)(       h    );
	bmpinfoheader[ 9] = (unsigned char)(       h>> 8);
	bmpinfoheader[10] = (unsigned char)(       h>>16);
	bmpinfoheader[11] = (unsigned char)(       h>>24);

	do
	{
		cout << "What is your text file Location? " << endl;
		getline(cin, fileLocation);

	}while(fileLocation.length() == 0);

	ifstream file;
	file.open(fileLocation);

	if(file.is_open())
	{
		char temp = ' ';
		string total;
		int i = 0;
		do
		{
			//Grab character
			while(file >> noskipws >> temp)
			{
				//Change the character to hex form
				total += HexTranslator::Transform(temp);
			}
		}while(!file.eof());
		file.close();

		int k = 0;
		for(int i=0; i<w; i++)
		{
			  for(int j=0; j<h; j++)
			{
				int x=i; 
				int y=(h-1)-j;
				img[(x+y*w)*3+2] = (unsigned char)(total[k]);
				if(k < total.size() - 1)
				{
					k += 1;
				}
				img[(x+y*w)*3+1] = (unsigned char)(total[k]);
				if(k < total.size()- 1)
				{
					k += 1;
				}
				img[(x+y*w)*3+0] = (unsigned char)(total[k]);
				if(k < total.size() - 1)
				{
					k += 1;
				}
			}
		}

		//Finish up BMP file save
		FILE* f = fopen("image.bmp", "wb");
		fwrite(bmpFileHeader, 1, 14, f);
		fwrite(bmpinfoheader, 1 ,40, f);
		for(int i = 0; i < h; i++)
		{	
			fwrite(img+(w*(h-i-1)*3),3,w,f);
			fwrite(bmppad,1,(4-(w*3)%4)%4,f);
		}
		fclose(f);
	}

	system("pause");
	return 0;
}