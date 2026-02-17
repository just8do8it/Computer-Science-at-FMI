package bg.sofia.uni.fmi.mjt.fittrack.workout;

import bg.sofia.uni.fmi.mjt.fittrack.exception.InvalidWorkoutException;

import java.lang.reflect.InaccessibleObjectException;

public non-sealed class CardioWorkout extends AbstractWorkout implements Workout {
    public CardioWorkout(String name, int duration, int caloriesBurned, int difficulty) throws InvalidWorkoutException {
        super(name, duration, caloriesBurned, difficulty);
        if (!validateData(name, duration, caloriesBurned, difficulty)) {
            throw new InvalidWorkoutException();
        }
    }

    @Override
    public WorkoutType getType() {
        return WorkoutType.CARDIO;
    }
}
