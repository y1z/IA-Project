#pragma once
#include <chrono>
#include <cinttypes>
/*!
 * \author Yhaliff said Barraza Zubia
 * \brief measures time and prints to the screen can also receive the time 
 elapsed in other time measurement.
 **/
class Timer
{
	/*! used for measuring durations in terms of picoseconds*/
	using TimeMeasurementNano = std::chrono::duration<uint64_t, std::nano>;

  using TimeMesuermentSeconds = std::chrono::duration<uint64_t, std::ratio<1,1>>; 
  
	/*! this duration has seconds that can have a decimal point
	(just because I get confused with other Representation)*/
	using TimeMeasurementSecondsDouble = std::chrono::duration<double, std::ratio<1, 1>>;

  /*! \returns the measured time in seconds*/
	using TimeMeasurementSecondsFloat = std::chrono::duration<float, std::ratio<1, 1>>;

	/*! making a typedef to be used with the chrono library*/
	using TimePointPicoSeconds = std::chrono::time_point<std::chrono::steady_clock, TimeMeasurementNano>;

public:// constructor
	Timer();
	~Timer();
public: // functions 

	void StartTiming();
	void EndTiming();

	int64_t GetResult();
	int64_t GetResultMicroSeconds();
	int64_t GetResultMiliSeconds();

	double GetResultSecondsDouble();
	float GetResultSecondsFloat();

	void PrintResult();
private:

private:// variables
	TimePointPicoSeconds m_Start;
	TimePointPicoSeconds m_End;

	TimeMeasurementNano m_Result;
};

