package bg.sofia.uni.fmi.mjt.fittrack.workout;

import bg.sofia.uni.fmi.mjt.fittrack.exception.InvalidWorkoutException;

public non-sealed class YogaSession extends AbstractWorkout implements Workout {
    public YogaSession(String name, int duration, int caloriesBurned, int difficulty) {
        super(name, duration, caloriesBurned, difficulty);
        if (!validateData(name, duration, caloriesBurned, difficulty)) {
            throw new InvalidWorkoutException();
        }
    }

    @Override
    public WorkoutType getType() {
        return WorkoutType.YOGA;
    }
}
