#include <stdio.h>

int main() {
    FILE *file = fopen("questiondata_en.csv", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    fprintf(file, "ID,Question,Category,Department,DateAdded,Status\n");
    fprintf(file, "000001,What is the company's vision and mission for the next 3-5 years?,Strategic Question,Management,06/10/2025,1\n");
    fprintf(file, "000002,What are the key objectives we need to achieve this quarter/year?,Strategic Question,Management,06/10/2025,1\n");
    fprintf(file, "000003,What is our position compared to competitors in the market?,Strategic Question,Management,06/10/2025,1\n");
    fprintf(file, "000004,What are the biggest challenges or risks the company is currently facing?,Strategic Question,Management,06/10/2025,1\n");
    fprintf(file, "000005,What kind of organizational culture do we want to build and maintain?,Strategic Question,Management,06/10/2025,1\n");
    fprintf(file, "000006,Who are our true target customers, and how well do we understand them?,Customer & Awareness Question,Marketing,06/10/2025,1\n");
    fprintf(file, "000007,Which channels generate the best engagement and reach our customers most effectively?,Customer & Awareness Question,Marketing,06/10/2025,1\n");
    fprintf(file, "000008,How do we measure the Return on Investment (ROI) of our marketing campaigns?,Customer & Awareness Question,Marketing,06/10/2025,1\n");
    fprintf(file, "000009,Is our marketing message clear and distinct from our competitors?,Customer & Awareness Question,Marketing,06/10/2025,1\n");
    fprintf(file, "000010,What new marketing trends should we consider adopting?,Customer & Awareness Question,Marketing,06/10/2025,1\n");
    fprintf(file, "000011,How realistic is this month's/quarter's sales target?,Revenue & Process Question,Sales,06/10/2025,1\n");
    fprintf(file, "000012,How effective is our sales pipeline, and where are the bottlenecks?,Revenue & Process Question,Sales,06/10/2025,1\n");
    fprintf(file, "000013,What are the main obstacles preventing the team from closing deals?,Revenue & Process Question,Sales,06/10/2025,1\n");
    fprintf(file, "000014,Which customer segments or products/services generate the most sales?,Revenue & Process Question,Sales,06/10/2025,1\n");
    fprintf(file, "000015,Does the sales team have adequate tools and information to succeed?,Revenue & Process Question,Sales,06/10/2025,1\n");
    fprintf(file, "000016,How can we attract and retain talented employees?,Personnel & Culture Question,Human Resources,06/10/2025,1\n");
    fprintf(file, "000017,What is our employee turnover rate, and what are its main causes?,Personnel & Culture Question,Human Resources,06/10/2025,1\n");
    fprintf(file, "000018,How satisfied and engaged are our employees with the organization?,Personnel & Culture Question,Human Resources,06/10/2025,1\n");
    fprintf(file, "000019,What is our plan for employee training and development?,Personnel & Culture Question,Human Resources,06/10/2025,1\n");
    fprintf(file, "000020,Is our salary structure and benefits package competitive in the market?,Personnel & Culture Question,Human Resources,06/10/2025,1\n");
    fprintf(file, "000021,What is the company's current cash flow situation?,Finance & Stability Question,Finance & Accounting,06/10/2025,1\n");
    fprintf(file, "000022,Where can we reduce unnecessary costs?,Finance & Stability Question,Finance & Accounting,06/10/2025,1\n");
    fprintf(file, "000023,Which products, services, or projects are the most and least profitable?,Finance & Stability Question,Finance & Accounting,06/10/2025,1\n");
    fprintf(file, "000024,What risks or opportunities do the financial reports reveal?,Finance & Stability Question,Finance & Accounting,06/10/2025,1\n");
    fprintf(file, "000025,Does the budget align with our actual operations?,Finance & Stability Question,Finance & Accounting,06/10/2025,1\n");
    fprintf(file, "000026,How can we improve efficiency in our production/service delivery process?,Efficiency & Quality Question,Operations / Production,06/10/2025,1\n");
    fprintf(file, "000027,Where are the bottlenecks in our workflow?,Efficiency & Quality Question,Operations / Production,06/10/2025,1\n");
    fprintf(file, "000028,How do we ensure consistent quality control for our products/services?,Efficiency & Quality Question,Operations / Production,06/10/2025,1\n");
    fprintf(file, "000029,Are there any issues in our supply chain and inventory management that need to be addressed?,Efficiency & Quality Question,Operations / Production,06/10/2025,1\n");
    fprintf(file, "000030,How can we reduce waste or errors in our work processes?,Efficiency & Quality Question,Operations / Production,06/10/2025,1\n");
    fprintf(file, "000031,What is our current Customer Satisfaction Score (CSAT)?,Satisfaction & Data Question,Customer Service,06/10/2025,1\n");
    fprintf(file, "000032,What are the most common issues customers contact us about, and how can we address the root cause?,Satisfaction & Data Question,Customer Service,06/10/2025,1\n");
    fprintf(file, "000033,What is our average time to resolve a customer issue?,Satisfaction & Data Question,Customer Service,06/10/2025,1\n");
    fprintf(file, "000034,How have we used customer feedback to improve our products or services?,Satisfaction & Data Question,Customer Service,06/10/2025,1\n");
    fprintf(file, "000035,Does the customer service team have sufficient tools and authority to help customers effectively?,Satisfaction & Data Question,Customer Service,06/10/2025,1\n");
    fprintf(file, "000036,If we had to start this department from scratch, with no limitations, what would we do differently?,Innovation & Growth Question,Other,06/10/2025,1\n");
    fprintf(file, "000037,If we had a 20% increase in budget and time, what project would we work on that we haven't been able to?,Innovation & Growth Question,Other,06/10/2025,1\n");
    fprintf(file, "000038,How can our department help [another department's name] achieve its goals more easily?,Inter-departmental Cooperation Question,Other,06/10/2025,1\n");
    fprintf(file, "000039,On a scale of 1-10, how smooth is our collaboration with other departments, and what would it take to make it a 10?,Inter-departmental Cooperation Question,Other,06/10/2025,1\n");
    fprintf(file, "000040,What is the single point of failure in our department's workflow?,Problem Solving & Risk Management Question,Other,06/10/2025,1\n");
    fprintf(file, "000041,What did we learn from our last major mistake, and what processes have we implemented to prevent it from happening again?,Problem Solving & Risk Management Question,Other,06/10/2025,1\n");
    fprintf(file, "000042,What data supported our department's most recent major decision?,Analysis & Data-Driven Question,Other,06/10/2025,1\n");
    fprintf(file, "000043,How well do the metrics we currently use reflect the true success of our department?,Analysis & Data-Driven Question,Other,06/10/2025,1\n");
    fclose(file);

    return 0;
}