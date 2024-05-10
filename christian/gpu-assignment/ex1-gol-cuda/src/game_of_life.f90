program game_of_life
    use cpu_game_of_life_mod, only: cpu_gol
    implicit none
    character(100) :: n_char, m_char, n_steps_char, exec_name
    integer :: n, m, n_steps
    real, dimension(:,:), allocatable :: random_matrix
    integer, dimension(:,:), allocatable:: initial_state, final_state
    real :: time_start, time_finish

    ! get program arguments
    call get_command(exec_name)
    if(command_argument_count() < 3) then
        print '(a, a20, a)', "Usage:", exec_name, "<n> <m> <n steps>"
        call exit(0)
    end if

    call get_command_argument(1, n_char); read(n_char, *) n
    call get_command_argument(2, m_char); read(m_char, *) m
    call get_command_argument(3, n_steps_char); read(n_steps_char, *) n_steps

    ! allocate arrays
    allocate(random_matrix(n, m), initial_state(n, m), final_state(n, m))
    
    ! initialise initial state 
    call random_number(random_matrix)
    initial_state = floor(random_matrix + 0.5)
    call cpu_time(time_start)
    call cpu_gol(initial_state, n_steps, final_state)
    call cpu_time(time_finish)
    print '("Execution time: ", f6.3, "s")', time_finish - time_start
    deallocate(random_matrix, initial_state, final_state)
end program game_of_life