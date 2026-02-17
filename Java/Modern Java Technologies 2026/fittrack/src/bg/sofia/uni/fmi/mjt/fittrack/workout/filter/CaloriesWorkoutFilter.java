package bg.sofia.uni.fmi.mjt.fittrack.workout.filter;

import bg.sofia.uni.fmi.mjt.fittrack.workout.Workout;

public class CaloriesWorkoutFilter implements WorkoutFilter {

    private final int minCalories;
    private final int maxCalories;

    public CaloriesWorkoutFilter(int min, int max) {
        this.minCalories = min;
        this.maxCalories = max;

        if (min > max || max < 0) {
            throw new IllegalArgumentException();
        }
    }
    @Override
    public boolean matches(Workout workout) {
        return workout.getDuration() > this.minCalories &&
                workout.getDuration() < this.maxCalories;
    }
}
