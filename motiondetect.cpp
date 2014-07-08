#define RGBSIZE 921600
//#define WSTEP 
 
 #include "cv.h" 
 #include "highgui.h" 
 #include <stdio.h>  

 #define MAX3(val1,val2,val3) ( ((val1) > (val2)) ? ((val1) > (val3)) ? (val1) : (val3) : ((val2) > (val3)) ? (val2) : (val3) )
 #define MIN3(val1,val2,val3) ( ((val1) < (val2)) ? ((val1) < (val3)) ? (val1) : (val3) : ((val2) < (val3)) ? (val2) : (val3) )

char ref[RGBSIZE];
IplImage* frame;

void printparam(int starting, int ending, int xinc, int yinc, int wstep, int num){
printf("number: %i\n\n",num);
printf("starting: %i\n",starting);
printf("ending: %i\n",ending);
printf("xinc: %i\n",xinc);
printf("yinc: %i\n",yinc);
printf("wstep: %i\n",wstep);

}

void viewcapspecs(CvCapture* cap, IplImage* pframe){
printf("widthstep: %i\n", pframe->widthStep );
printf("imagesize: %i\n", pframe->imageSize );
printf("dataorder: %i\n", pframe->dataOrder );
//printf();
//printf();
//printf();
}

void getref(){
	for(int I = 0; I < RGBSIZE; I++){
		ref[I]= frame->imageData[I];
	}
}


void paintframewhite(int starting, int ending, int xinc, int yinc, int wstep){
//printparam( starting, ending, xinc, yinc, wstep,6);	
	int initstarting = starting;
	int initending = ending;
	for(int I = starting; I < ending; I+=wstep){
		for(int J = starting; J < starting+xinc; J++){
		
		frame->imageData[J] = 255;
		}
	starting+=wstep;
	}
//printparam( starting, ending, xinc, yinc, wstep,7);
}

void paintframeblack(int starting, int ending, int xinc, int yinc, int wstep){
//printparam( starting, ending, xinc, yinc, wstep,4);	
	int initstarting = starting;
	int initending = ending;
	for(int I = starting; I < ending; I+=wstep){
		for(int J = starting; J < starting+xinc; J++){

		frame->imageData[J] = 0;
		}
	starting+=wstep;
	}
//printparam( starting, ending, xinc, yinc, wstep,5);
}

int getdiffarea(int starting, int ending, int xinc, int yinc, int wstep){
//printparam( starting, ending, xinc, yinc, wstep,2);	
	int numdiff = 0;
	int initstarting, initending;
	initstarting = starting;
	initending = ending;
	for(int I = starting; I < ending; I+=wstep){
		for(int J = starting; J < starting+xinc; J+=3){
			if(abs((int)(unsigned char)ref[J]-(int)(unsigned char)frame->imageData[J])>50&&abs((int)(unsigned char)ref[J]-(int)(unsigned char)frame->imageData[J])<200){
			numdiff++;
			}
		
		}
	starting+=wstep;
	}
	//printf("numdiff %i \n",numdiff);
	//if more than half of area of roi is signifigantly different, do paint frame white else black
	if(numdiff>(500)/2){
	//printf("white \n");
	paintframewhite(initstarting,initending,xinc,yinc,wstep);
	}else{
	paintframeblack(initstarting,initending,xinc,yinc,wstep);
	}
//printparam( starting, ending, xinc, yinc, wstep, 3);
}


void roimanager(int framediv, int wstep){//framediv =  # frame divisions

	int starting =0;
	int ending =0; 
	int xterm =0; 
	int yterm = 0;
	int xinc = wstep/sqrt(framediv); //a widthstep divided by 6
	int yinc = ((RGBSIZE/wstep)/sqrt(framediv))*wstep;//number of widthsteps divided by 6

		for(int J = 0; J < sqrt(framediv); J++){
			for(int K = 0; K < sqrt(framediv); K++){
			starting = (J*yinc)+(K*xinc);
			ending = (starting+yinc)+(xinc);
			getdiffarea(starting, ending, xinc, yinc, wstep);

			}

		}

//printparam( starting, ending, xinc, yinc, wstep,1);
}


void ipltograyscale(){
for(int I = 0; I < RGBSIZE; I+=3){
     //int max = MAX3(frame->imageData[I],frame->imageData[I+1],frame->imageData[I+2]);
     //frame->imageData[I] = max;
     frame->imageData[I+1] = frame->imageData[I];
     frame->imageData[I+2] = frame->imageData[I];
     }

}

 int main() {
  // printf("1\n");
   
   CvCapture* capture = cvCaptureFromCAM(0);
  // cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 240);
  // cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 320);
   cvNamedWindow( "mywindow", CV_WINDOW_AUTOSIZE );
   sleep(3);
   frame = cvQueryFrame(capture);
   viewcapspecs(capture, frame);
   ipltograyscale();
  getref();
   int wstep = frame->widthStep;
   while(1){
     frame = cvQueryFrame(capture);
     //convert frame to intensity
     ipltograyscale();
     //getref();
     //frame = cvQueryFrame(capture);
     roimanager(400, wstep);

     cvShowImage( "mywindow", frame );
     //getref();
     if((cvWaitKey(10) & 255) == 27) break;	
   }
   cvReleaseCapture( &capture );
   cvDestroyWindow( "mywindow" );
   return 0;
 }
