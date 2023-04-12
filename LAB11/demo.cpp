#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <math.h>

#define NODE_COUNT 20
#define INTERVAL 1 // Interval between synchronizations in seconds

int main()
{
    struct timeval offset[NODE_COUNT]; // Clock offsets for each node
    double drift[NODE_COUNT];          // Clock drift rates for each node
    double time[NODE_COUNT];           // Current time for each node
    double sum_of_offsets;             // Sum of clock offsets across all nodes
    double avg_offset;                 // Average clock offset across all nodes
    double sum_of_drifts;              // Sum of clock drift rates across all nodes
    double avg_drift;                  // Average clock drift rate across all nodes
    double error[NODE_COUNT];          // Clock error for each node
    double max_error;                  // Maximum clock error across all nodes
    double delta;                      // Adjustment to clock rate

    int i, j;

    // Initialize clock offsets and drift rates for each node
    for (i = 0; i < NODE_COUNT; i++)
    {
        offset[i].tv_sec = rand() % 60;                                 // Initialize to a random offset between 0 and 59 seconds
        offset[i].tv_usec = rand() % 1000000;                           // Initialize to a random offset between 0 and 999,999 microseconds
        drift[i] = (rand() % 100) / 1000.0;                             // Initialize to a random drift rate between 0 and 0.1 seconds per second
        time[i] = i + offset[i].tv_sec + offset[i].tv_usec / 1000000.0; // Initialize current time based on offset
    }

    // Synchronize clocks at regular intervals
    while (1)
    {
        // Calculate average clock offset and drift rate across all nodes
        sum_of_offsets = 0;
        sum_of_drifts = 0;
        for (i = 0; i < NODE_COUNT; i++)
        {
            sum_of_offsets += offset[i].tv_sec + offset[i].tv_usec / 1000000.0;
            sum_of_drifts += drift[i];
        }
        avg_offset = sum_of_offsets / NODE_COUNT;
        avg_drift = sum_of_drifts / NODE_COUNT;

        // Update clock offsets and drift rates for each node
        for (i = 0; i < NODE_COUNT; i++)
        {
            error[i] = time[i] - (i + avg_offset);                          // Calculate clock error for node i
            offset[i].tv_sec -= floor(error[i]);                            // Adjust clock offset for node i
            offset[i].tv_usec -= (error[i] - floor(error[i])) * 1000000;    // Adjust clock offset for node i
            drift[i] += error[i] * avg_drift;                               // Adjust clock drift rate for node i
            time[i] = i + offset[i].tv_sec + offset[i].tv_usec / 1000000.0; // Update current time for node i
        }

        // Calculate maximum clock error across all nodes
        max_error = 0;
        for (i = 0; i < NODE_COUNT; i++)
        {
            if (fabs(error[i]) > max_error)
            {
                max_error = fabs(error[i]);
            }
        }

        // Print clock offset, drift rate, and error for each node
        printf("Node\tOffset\tDrift\tError\n");
        for (i = 0; i < NODE_COUNT; i++)
        {
            printf("%d\t%.6f\t%.6f\t%.6f\n", i, offset[i].tv_sec + offset[i].tv_usec / 1000000.0, drift[i], error[i]);
        }
        // Calculate maximum clock error across all nodes
        max_error = 0;
        for (i = 0; i < NODE_COUNT; i++)
        {
            if (fabs(error[i]) > max_error)
            {
                max_error = fabs(error[i]);
            }
        }

        // Print maximum clock error
        printf("Max error: %.6f seconds\n", max_error);

        // Adjust clock rate if maximum error exceeds threshold
        if (max_error > 0.1)
        { // Threshold for adjusting clock rate
            delta = (avg_drift / NODE_COUNT) * (max_error / 2);
            for (i = 0; i < NODE_COUNT; i++)
            {
                drift[i] -= delta;
            }
        }

        // Wait for next synchronization interval
        sleep(INTERVAL);
    }

    return 0;
}
