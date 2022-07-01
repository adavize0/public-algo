// Makes a single trains array, sorted chronologically with their arrival times
function makeTrainsArray(arrivals, departures, n) {
    const trainsArr = new Array(n)
    for (let i = 0; i < n; i++) {
        trainsArr[i] = {
            arrivedAt: arrivals[i],
            departsAt: departures[i]
        }
    }

    // Sort data according to arrival time
    trainsArr.sort((a, b) => a.arrivedAt - b.arrivedAt)
    return trainsArr;
}

function findMinimumPlatforms(arrivals, departures, n) {
    const trains = makeTrainsArray(arrivals, departures, n)


    let virtualClockTime = 0;
    let maxTrainsWaiting = 0;
    // Using a JavaScript set because deleting an item is straightforward, compared to arrays
    let virtualQueue = new Set();


    // Taking each train sequentially to simulate arrivals
    for (let newlyArrivedTrain of trains) {
        // Update present moment to the time of newly arrived train
        virtualClockTime = newlyArrivedTrain.arrivedAt;


        // Remove supposedly departed trains from the virtual queue…
        // … using the present time
        for (let train of virtualQueue) {
        
            if (train.departsAt < virtualClockTime) {
                virtualQueue.delete(train);
            }
        }


        // Add newly arrived train to virtual queue
        virtualQueue.add(newlyArrivedTrain);


        // Keep track of the maximum number of trains queueing at this particular time
        maxTrainsWaiting = Math.max(maxTrainsWaiting, virtualQueue.size);
    }


    return maxTrainsWaiting;


}

const arrivals = [ 900, 940, 950, 1100, 1500, 1800 ];
const departures = [ 910, 1200, 1120, 1130, 1900, 2000 ];
const n = arrivals.length;

const result = findMinimumPlatforms(arrivals, departures, n);
console.log(result);
