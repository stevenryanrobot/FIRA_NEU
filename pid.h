#ifndef _PID_HEADER_
#define _PID_HEADER_
//PID 
class PID{
public:
	//let the private value equivalent the param 
	PID(double _Kp = 0.0, double _Ki = 0.0, double _Kd = 0.0, double _maxSum = 10.0, double _minErr = 0.1) : Kp(_Kp), Ki(_Ki), Kd(_Kd), maxSum(_maxSum), minErr(_minErr)
	{
		sum = 0;
		last = 0;

	}
	~PID(){};
	// Error power function
	double run(double err)
	{
		//Integal Error maxSum judgement
		if(abs(err)<minErr){sum = 0;}//自动刷新
		if(sum <= maxSum || maxSum == 0){sum += err;}//modified by donqianli没有负向积分
		if (sum <= -maxSum)sum = -maxSum;
		if (sum >= maxSum)sum = maxSum;
		//PID control system
		lastOut = (Kp*err)+(Ki*sum)+(Kd*(err-last));
		//dereive Error represent or on behalf of the the before Error
		last = err;
		if (lastOut > maxoutput)lastOut = maxoutput;
		if (lastOut < -maxoutput)lastOut = -maxoutput;
		return lastOut;
	}
	double lastOut;
	double Kp, Ki, Kd;
	double maxSum, minErr,maxoutput;
	
	double abs(double v){return(v>0)?v:-v;}
	double sum;
	double last;
};
#endif