package bg.sofia.uni.fmi.mjt.burnout.semester;

import bg.sofia.uni.fmi.mjt.burnout.exception.DisappointmentException;
import bg.sofia.uni.fmi.mjt.burnout.exception.InvalidSubjectRequirementsException;
import bg.sofia.uni.fmi.mjt.burnout.plan.SemesterPlan;
import bg.sofia.uni.fmi.mjt.burnout.subject.UniversitySubject;

public non-sealed class ComputerScienceSemesterPlanner implements SemesterPlannerAPI {
    @Override
    public UniversitySubject[] calculateSubjectList(SemesterPlan semesterPlan) throws InvalidSubjectRequirementsException {
        CalcSubjectsCheckForExceptions(semesterPlan);

        int totalRating = 0;
        for (UniversitySubject subject : semesterPlan.subjects()) {
            totalRating += subject.rating();
        }

        int n = semesterPlan.subjects().length;

        double avgRating = (double) totalRating / (double) n;
        double lastAvgRating = 0;
        UniversitySubject[] chosen = new UniversitySubject[n];
        int totalChosenCredits = 0;
        int counter = 0;
        while (totalChosenCredits < semesterPlan.minimalAmountOfCredits()) {
            for (int i = 0; i < n; ++i) {
                if (semesterPlan.subjects()[i].rating() < avgRating &&
                        semesterPlan.subjects()[i].rating() > lastAvgRating ) {
                    chosen[counter] = semesterPlan.subjects()[i];
                    totalChosenCredits += semesterPlan.subjects()[i].credits();
                    counter++;
                }
            }
            lastAvgRating = avgRating;
            avgRating = (avgRating + 5) / 2.0;
        }

        return chosen;
    }
}
