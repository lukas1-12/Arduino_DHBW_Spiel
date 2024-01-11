## Schedule

```mermaid
gantt
    tickInterval 4week
    weekday monday
    dateFormat YYYY-MM-DD
    section Software
        Software Architecture design        :a1, 2024-01-13, 3d
        Software Prototype Implementation   :a2, after a1, 20d
        Software Prototype Testing          :a3, 2024-01-20, 20d
        Software Implemantation and Testing of special Features :2024-02-10, 2024-08-01
    section Hardware
        Prototype Hardware Purchasing       :b1, 2024-01-10, 5d
        Prototype build                     :after b1, 24d
    section Management
        writing Prototype Documentation     :c1, 2024-01-18, 2024-02-22
        Define Requirements                 :c2, 2024-01-08, 2024-01-13
    section Milestones
        Entering Engineering Phase          :milestone, 2023-12-07
        Entering Design Phase               :milestone, 2024-01-13
        Entering Implementation Phase       :milestone, with a2
        Entering Validation Phase           :milestone, 2024-02-12
        working Prototype                   :milestone, 2024-02-22 
        Prototype Presentation              :milestone, 2024-03-14
        Product Release                     :milestone, 2024-08-14
```