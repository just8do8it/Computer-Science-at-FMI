package bg.sofia.uni.fmi.mjt.burnout.semester;

import bg.sofia.uni.fmi.mjt.burnout.exception.CryToStudentsDepartmentException;
import bg.sofia.uni.fmi.mjt.burnout.exception.DisappointmentException;
import bg.sofia.uni.fmi.mjt.burnout.exception.InvalidSubjectRequirementsException;
import bg.sofia.uni.fmi.mjt.burnout.plan.SemesterPlan;
import bg.sofia.uni.fmi.mjt.burnout.subject.SubjectRequirement;
import bg.sofia.uni.fmi.mjt.burnout.subject.UniversitySubject;

public sealed interface SemesterPlannerAPI permits SoftwareEngineeringSemesterPlanner, ComputerScienceSemesterPlanner {

    /**
     * Calculates the subject combination for this semester type based on the subjectRequirements.
     *
     * @param semesterPlan the current semester plan needed for the calculation
     * @throws CryToStudentsDepartmentException when a student cannot cover his semester credits.
     * @throws IllegalArgumentException if the semesterPlan is missing or is null
     * @throws InvalidSubjectRequirementsException if the subjectRequirements contain duplicate categories
     * @return the subject list that balances credits, study time, and requirements
     */
    UniversitySubject[] calculateSubjectList(SemesterPlan semesterPlan) throws InvalidSubjectRequirementsException;

    /**
     * Calculates the amount of jars grandma will send you
     *
     * @param subjects the subjects to calculate jar count for
     * @param maximumSlackTime the rest days grandma gave as limit before stopping the jar food deliveries
     * @param semesterDuration the duration of the semester in days
     * @throws IllegalArgumentException if the subjects are missing or null, or maximumSlackTime/semesterDuration are not positive integers
     * @throws DisappointmentException if you cannot make grandma happy.
     *
     * @return the number of jars grandma sends that are needed for survival
     */
    default int calculateJarCount(UniversitySubject[] subjects, int maximumSlackTime, int semesterDuration) {
        if (maximumSlackTime < 0 || semesterDuration < 0 ||
                subjects == null || subjects.length == 0) {
            throw new IllegalArgumentException();
        }

        double restNeeded = 0.0;
        int studyTimeNeeded = 0;
        for (UniversitySubject subject : subjects) {
            if (subject == null) break;
            switch (subject.category()) {
                case MATH -> restNeeded += subject.neededStudyTime() * 0.2;
                case PROGRAMMING -> restNeeded += subject.neededStudyTime() * 0.1;
                case THEORY -> restNeeded += subject.neededStudyTime() * 0.15;
                case PRACTICAL -> restNeeded += subject.neededStudyTime() * 0.05;
            }

            studyTimeNeeded += subject.neededStudyTime();
        }

        if (maximumSlackTime < restNeeded) {
            throw new DisappointmentException();
        }

        int jarCount = semesterDuration / 5;
        if (restNeeded + studyTimeNeeded > semesterDuration) {
            jarCount *= 2;
        }

        return jarCount;
    }

    default void CalcSubjectsCheckForExceptions(SemesterPlan semesterPlan) throws InvalidSubjectRequirementsException {
        if (semesterPlan == null || semesterPlan.subjects().length == 0) {
            throw new IllegalArgumentException();
        }
        int semesterCredits = 0;
        for (UniversitySubject subject : semesterPlan.subjects()) {
            semesterCredits += subject.credits();
        }
        if (semesterCredits < semesterPlan.minimalAmountOfCredits()) {
            throw new CryToStudentsDepartmentException("Not enough credits ;-;");
        }

        if (semesterPlan.subjectRequirements().length > 4) {
            throw new InvalidSubjectRequirementsException();
        }
        else {
            int math = 0, prog = 0, theory = 0, pract = 0;
            for (SubjectRequirement currReq : semesterPlan.subjectRequirements()) {
                switch (currReq.category()) {
                    case MATH -> math++;
                    case PROGRAMMING -> prog++;
                    case THEORY -> theory++;
                    case PRACTICAL -> pract++;
                }
            }
            if (math > 1 || prog > 1 || theory > 1 || pract > 1) {
                throw new InvalidSubjectRequirementsException();
            }
        }
    }
}