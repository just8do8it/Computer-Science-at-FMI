import bg.sofia.uni.fmi.mjt.fittrack.FitPlanner;
import bg.sofia.uni.fmi.mjt.fittrack.exception.OptimalPlanImpossibleException;
import bg.sofia.uni.fmi.mjt.fittrack.workout.CardioWorkout;
import bg.sofia.uni.fmi.mjt.fittrack.workout.StrengthWorkout;
import bg.sofia.uni.fmi.mjt.fittrack.workout.Workout;
import bg.sofia.uni.fmi.mjt.fittrack.workout.YogaSession;

import java.util.Arrays;
import java.util.List;

public class Main {
    public static void main(String[] args) throws OptimalPlanImpossibleException {
        List<Workout> workouts = Arrays.asList(
                new CardioWorkout("HIIT", 30, 400, 4),
                new StrengthWorkout("Upper Body", 45, 350, 3),
                new YogaSession("Morning Flow", 20, 150, 2),
                new CardioWorkout("Cycling", 60, 600, 5),
                new StrengthWorkout("Leg Day", 30, 250, 2),
                new YogaSession("Evening Relax", 15, 100, 1)
        );

        FitPlanner planner = new FitPlanner(workouts);
        List<Workout> plan = planner.generateOptimalWeeklyPlan(120);

        for (Workout w : plan) {
            System.out.println(w);
        }

        // CardioWorkout[name=Cycling, duration=60, caloriesBurned=600, difficulty=5]
        // CardioWorkout[name=HIIT, duration=30, caloriesBurned=400, difficulty=4]
        // StrengthWorkout[name=Leg Day, duration=30, caloriesBurned=250, difficulty=2]
    }
}