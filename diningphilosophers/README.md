# Dining Philosophers Problem

> solving dining philosophers problem with threads & locks.

![solution](https://github.com/IlayG01/os_concepts_windows/blob/master/diningphilosophers/Images/problem.jpg)

## External Resources

- https://en.wikipedia.org/wiki/Dining_philosophers_problem
- https://en.wikipedia.org/wiki/Critical_section
- https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-entercriticalsection
- https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-tryentercriticalsection

### Solution Explanation

each thread symbolize a philosopher
each critical section symbolize a fork/stick
we want to make sure that there will be no starvation(1 philosopher that doesn't eat) or deadlocks.

solution -
creating 5 philosophers, 5 forks/sticks.
each philosopher will try to pick the left fork till he succeed(EnterCriticalSection).
then philosopher will try to pick the right fork only once to eat(TryEnterCriticalSection).
if succeed - eats.
else - return his left fork to table.

Deadlock & Starvation free.

### Credit

- Ilay Gilman
