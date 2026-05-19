from __future__ import annotations


def needleman_wunsch(
    sequence1: str,
    sequence2: str,
    match_score: int = 1,
    mismatch_score: int = -1,
    gap_penalty: int = -1,
) -> tuple[int, str, str]:
    rows = len(sequence1) + 1
    columns = len(sequence2) + 1

    score = [[0] * columns for _ in range(rows)]

    for i in range(1, rows):
        score[i][0] = i * gap_penalty
    for j in range(1, columns):
        score[0][j] = j * gap_penalty

    for i in range(1, rows):
        for j in range(1, columns):
            diagonal = score[i - 1][j - 1] + (
                match_score if sequence1[i - 1] == sequence2[j - 1] else mismatch_score
            )
            up = score[i - 1][j] + gap_penalty
            left = score[i][j - 1] + gap_penalty
            score[i][j] = max(diagonal, up, left)

    aligned1: list[str] = []
    aligned2: list[str] = []
    i = len(sequence1)
    j = len(sequence2)

    while i > 0 or j > 0:
        if i > 0 and j > 0:
            diagonal_score = score[i - 1][j - 1] + (
                match_score if sequence1[i - 1] == sequence2[j - 1] else mismatch_score
            )
            if score[i][j] == diagonal_score:
                aligned1.append(sequence1[i - 1])
                aligned2.append(sequence2[j - 1])
                i -= 1
                j -= 1
                continue

        if i > 0 and score[i][j] == score[i - 1][j] + gap_penalty:
            aligned1.append(sequence1[i - 1])
            aligned2.append("-")
            i -= 1
        else:
            aligned1.append("-")
            aligned2.append(sequence2[j - 1])
            j -= 1

    aligned1.reverse()
    aligned2.reverse()
    return score[-1][-1], "".join(aligned1), "".join(aligned2)


def main() -> None:
    sequence1 = "GATTACA"
    sequence2 = "GCATGCU"

    score, aligned1, aligned2 = needleman_wunsch(sequence1, sequence2)

    print(f"Sequence 1: {sequence1}")
    print(f"Sequence 2: {sequence2}")
    print(f"Alignment score: {score}")
    print(aligned1)
    print(aligned2)


if __name__ == "__main__":
    main()
