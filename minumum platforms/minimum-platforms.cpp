#include <iostream>

// The next two imports can be reduced to #include <bits/stdc++.h>, depending on your compiler.
#include <algorithm> // We'll need this for sorting

#include <queue> // We'll need this for the priority queue (or min heap)

using namespace std;

struct TrainData {
  int arrivedAt;
  int departsAt;
};

// Helper function for sorting with arrival times
static bool compareArrivalTimes(TrainData trainA, TrainData trainB) {
  return (trainA.arrivedAt < trainB.arrivedAt);
}

// Helper function to make a trains array sorted chronologically with their arrival times
TrainData * makeTrainsArray(int arrivals[], int departures[], int n) {
  TrainData * trains = new TrainData[n];

  for (int i = 0; i < n; ++i) {
    // Make a new train data using the defined struct
    TrainData train;
    train.arrivedAt = arrivals[i];
    train.departsAt = departures[i];

    trains[i] = train;
  }

  sort(trains, trains + n, compareArrivalTimes);
  return trains;
}

int findMinimumPlatforms(int arrivals[], int departures[], int n) {
  const TrainData * trains = makeTrainsArray(arrivals, departures, n);

  int virtualClockTime = 0;
  int maxTrainsWaiting = 0;

  // Using a priority queue data structure for the virtual queue.
  priority_queue < int > virtualQueue;

  for (int i = 0; i < n; ++i) {
    // Update present moment to the time of newly arrived train
    virtualClockTime = trains[i].arrivedAt;

    // Remove supposedly departed trains from the virtual queue by using the present time.
    while (!virtualQueue.empty()) {
      int departureTime = virtualQueue.top() * -1;
      if (departureTime < virtualClockTime) {
        virtualQueue.pop();
      } else {
        // We can break out of the loop here because all departed trains have been removed.
        break;
      }

    }

    // Add newly arrived train to queue (note we are storing only the time in the priority queue)
    virtualQueue.push(trains[i].departsAt * -1);

    // Keep track of the maximum number of trains queueing at this particular time
    maxTrainsWaiting = maxTrainsWaiting > virtualQueue.size() ? maxTrainsWaiting : virtualQueue.size();

  }

  // Free up allocated memory ;)
  delete trains;
  return maxTrainsWaiting;
}


int main(){
	
	int arrivals[] = {900, 940, 950, 1100, 1500, 1800};
	int departures[] =  {910, 1200, 1120, 1130, 1900, 2000};

	int answer = findMinimumPlatforms(arrivals, departures, sizeof(arrivals));
	cout << "Minimum platforms required: " << answer << endl;

	system("PAUSE");
	return 0;
}
