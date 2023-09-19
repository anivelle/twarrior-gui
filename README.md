# twarrior-gui

This is a Qt-based GUI for Task and Timewarrior. I recently began using these
programs and they've been super neat, but I want to be able to view manage my
tasks outside of the command line. I originally tried using the widget system in
AwesomeWM, but I cannot wrap my head around it for some reason. Might give it
another go in the future. With Qt, though, this program is more portable. As
with my [ray tracer][ray-tracer] project, this repository will really serve me
for everything as I work through the intricacies of Qt.

# Current Progress

- Moved to Qt from GTK, basically resetting the minimal progress I had

# Goals

## Taskwarrior

- List of tasks
  - List items show description, due date, top tag, and urgency
  - Tasks can be added from list
  - Sort by due date, urgency, description, tags, etc
  - Filter tasks by context and/or tags
- Task addition and modification
  - All available fields should be modifiable
  - Maybe hide some less-used fields under an "Advanced" tag
- Calendar/deadline view

## Timewarrior

- Likely a lot simpler
- List of tags
  - Show currently running (if any) at the top
  - Tag search
  - List items allow for start/stop of tag
  - Track previous time spent on tag
- Day/week/month summary
  - Could start as just text-based but have a calendar view later
  - Allow tagging/untagging time sections, modifying start/end, deleting
    sections

[ray-tracer]: https://github.com/anivelle/misc-projects/tree/main/ray-tracing
