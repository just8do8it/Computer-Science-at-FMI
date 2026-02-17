package bg.sofia.uni.fmi.mjt.fittrack.workout.filter;

import bg.sofia.uni.fmi.mjt.fittrack.workout.Workout;
import bg.sofia.uni.fmi.mjt.fittrack.workout.WorkoutType;

public class TypeWorkoutFilter implements WorkoutFilter {

    private final WorkoutType type;

    public TypeWorkoutFilter(WorkoutType type) {
        this.type = type;
        if (type == null) {
            throw new IllegalArgumentException();
        }
    }
    @Override
    public boolean matches(Workout workout) {
        return workout.getType().equals(this.type);
    }
}
