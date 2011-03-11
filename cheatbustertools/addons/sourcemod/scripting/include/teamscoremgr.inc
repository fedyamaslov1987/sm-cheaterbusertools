#if defined _teamscoremgr_included_
  #endinput
#endif
#define _teamscoremgr_included_


/**
 * Set team score to defined state
 *
 * @param team		Team number, 2 - terrorist 3- ct, other = ignored
 * @noreturn
 */
native SetTeamScoreEx(team,score);
/**
 * Get Team Score
 *
 * @param team		Team number, 2 - terrorist 3- ct, other = ignored
 * @return		Team score in int
 */
native GetTeamScoreEx(team);
/**
 * Swap Team Scores
 *
 * @noparam
 * @noreturn
 */
native TeamScoreSwap();
/**
 * Reset team scores to 0
 *
 * @noparam
 * @noreturn
 */
native TeamScoreReset();