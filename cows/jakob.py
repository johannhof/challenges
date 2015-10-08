array = [
    True, True, True, False, True, True, False, False, True, True, False, True]

# One cut is always needed, as the plank is infinitely long.
best_with_gap = 5
best_without_gap = 5

previous = False

for current in array:

    if current:
        if previous:
            # We have wood already
            best_without_gap += 3
            best_with_gap += 3
        else:
            best_with_gap = best_without_gap = (
                min(best_with_gap, best_without_gap) + 3)

    else:
        if previous:
            # Just ended
            best_with_gap += 5 # The cut
            best_without_gap += 3 # Continue the wood
        else:
            # Continuing a gap
            best_without_gap += 3
            # With gap this is free

    previous = current

print min(best_with_gap, best_without_gap)

