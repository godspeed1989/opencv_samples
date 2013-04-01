#include <cv.h>
#include <ml.h>

// The neural network
CvANN_MLP machineBrain;

// Read the training data and train the network.
void trainMachine()
{
	int i;
	//The number of training samples. 
	int train_sample_count;

	//The training data matrix. 
	//Note that we are limiting the number of training data samples to 1000 here.
	//The data sample consists of two inputs and an output. That's why 3.
	float td[1000][3];

	//Read the training file
	/* A sample file contents(say we are training the network for generating
	   the mean given two numbers) would be:
	5
	12 16 14
	10 5  7.5
	8  10 9
	5  4  4.5
	12 6  9
	*/
	FILE *fin;
	fin = fopen("train.txt", "r");

	//Get the number of samples.
	fscanf(fin, "%d", &train_sample_count);
	printf("Found training file with %d samples...\n", train_sample_count);

	//Create the matrices
	//Input data samples. Matrix of order (train_sample_count x 2)
	CvMat* trainData = cvCreateMat(train_sample_count, 2, CV_32FC1);

	//Output data samples. Matrix of order (train_sample_count x 1)
	CvMat* trainClasses = cvCreateMat(train_sample_count, 1, CV_32FC1);

	//The weight of each training data sample. We'll later set all to equal weights.
	CvMat* sampleWts = cvCreateMat(train_sample_count, 1, CV_32FC1);

	//The matrix representation of our ANN. We'll have four layers.
	CvMat* neuralLayers = cvCreateMat(4, 1, CV_32SC1);

	CvMat trainData1, trainClasses1, sampleWts1, neuralLayers1;

	cvGetRows(trainData, &trainData1, 0, train_sample_count);
	cvGetRows(trainClasses, &trainClasses1, 0, train_sample_count);
	cvGetRows(sampleWts, &sampleWts1, 0, train_sample_count);
	cvGetRows(neuralLayers, &neuralLayers1, 0, 4);

	//Setting the number of neurons on each layer of the ANN
	/* 
	We have in	Layer 1: 2 neurons (2 inputs)
				Layer 2: 3 neurons (hidden layer)
				Layer 3: 3 neurons (hidden layer)
				Layer 4: 1 neurons (1 output)
	*/
	cvSet1D(&neuralLayers1, 0, cvScalar(2));
	cvSet1D(&neuralLayers1, 1, cvScalar(3));
	cvSet1D(&neuralLayers1, 2, cvScalar(3));
	cvSet1D(&neuralLayers1, 3, cvScalar(1));

	//Read and populate the samples.
	for (i=0;i<train_sample_count;i++)
		fscanf(fin,"%f %f %f",&td[i][0],&td[i][1],&td[i][2]);

	fclose(fin);

	//Assemble the ML training data.
	for (i=0; i<train_sample_count; i++)
	{
		//Input 1
		cvSetReal2D(&trainData1, i, 0, td[i][0]);
		//Input 2
		cvSetReal2D(&trainData1, i, 1, td[i][1]);
		//Output
		cvSet1D(&trainClasses1, i, cvScalar(td[i][2]));
		//Weight (setting everything to 1)
		cvSet1D(&sampleWts1, i, cvScalar(1));
	}

	//Create our ANN.
	machineBrain.create(neuralLayers);

	//Train it with our data.
	machineBrain.train(
		trainData,
		trainClasses,
		sampleWts,
		0,
		CvANN_MLP_TrainParams(
			cvTermCriteria(
				CV_TERMCRIT_ITER+CV_TERMCRIT_EPS,
				100000,
				1.0
			),
			CvANN_MLP_TrainParams::BACKPROP,
			0.01,
			0.05
		)
	);
}

// Predict the output with the trained ANN given the two inputs.
void Predict(float data1, float data2)
{
	float _sample[2];
	CvMat sample = cvMat(1, 2, CV_32FC1, _sample);
	float _predout[1];
	CvMat predout = cvMat(1, 1, CV_32FC1, _predout);
	sample.data.fl[0] = data1;
	sample.data.fl[1] = data2;

	machineBrain.predict(&sample, &predout);

	printf("%f \n", predout.data.fl[0]);
}

int main()
{
	int wait;

	// Train the neural network  with the samples
	trainMachine();

	// Now try predicting some values with the trained network
	Predict(15.0, 20.0);
	Predict(1.0, 5.0);
	Predict(12.0, 3.0);

	return 0;
}

