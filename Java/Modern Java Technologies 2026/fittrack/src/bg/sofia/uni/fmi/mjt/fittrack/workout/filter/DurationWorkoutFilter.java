package bg.sofia.uni.fmi.mjt.fittrack.workout.filter;

import bg.sofia.uni.fmi.mjt.fittrack.workout.Workout;

public class DurationWorkoutFilter implements WorkoutFilter {
    private final int minDuration;
    private final int maxDuration;

    public DurationWorkoutFilter(int min, int max) {
        this.minDuration = min;
        this.maxDuration = max;

        if (min > max || max < 0) {
            throw new IllegalArgumentException();
        }
    }

    @Override
    public boolean matches(Workout workout) {
        return workout.getDuration() > this.minDuration &&
                workout.getDuration() < this.maxDuration;
    }
}
