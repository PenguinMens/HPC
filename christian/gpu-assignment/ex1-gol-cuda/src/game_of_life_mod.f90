module cpu_game_of_life_mod
    implicit none

    integer, parameter :: ALIVE = 1
    integer, parameter :: DEAD = 0
    
    contains
    subroutine print_grid(grid)
        implicit none
        integer, dimension(:,:), intent(in) :: grid

        integer :: n, m, i

        n = size(grid, 1)
        m = size(grid, 2)

        do i = 1, n
            print *, grid(i, 1:m)
        end do
    end subroutine print_grid

    function cpu_count_neighbours(x, y, grid) result(n_neighbours)
        implicit none
        integer, intent(in) :: x, y ! coordinates for the cell whose neighbours we want to count
        integer, dimension(:, :), intent(in) :: grid
        integer :: n_neighbours
        integer :: i, j, n, m, n_x, n_y
        
        n = size(grid, 1)
        m = size(grid, 2)

        n_neighbours = 0
        do i = -1, 1
            n_x = x + i
            if (n_x < 1 .or. n_x > n) then
                cycle
            end if    
            do j = -1, 1
                n_y = y + j
                if (n_y < 1 .or. n_y > m .or. (n_x == x .and. n_y == y)) then
                    cycle
                end if
                ! check cell status
                if (grid(n_x, n_y) == ALIVE) then
                    n_neighbours = n_neighbours + 1
                end if
            end do
        end do
    end function cpu_count_neighbours


    subroutine cpu_gol_step(current_grid, next_grid)
        implicit none
        integer, dimension(:, :), intent(in) :: current_grid
        integer, dimension(:, :), intent(out) :: next_grid
        integer :: i, j, n, m, n_neighbours, current_cell

        n = size(current_grid, 1)
        m = size(current_grid, 2)

        ! start of the code
        do j = 1, m ! for each column
            do i = 1, n ! for each row
                current_cell = current_grid(i, j)
                n_neighbours = cpu_count_neighbours(i, j, current_grid)
                if (current_cell == ALIVE  .and. (n_neighbours == 2 .or. n_neighbours == 3)) then
                    next_grid(i, j) = ALIVE
                else if (current_cell == DEAD .and.  n_neighbours == 3) then
                    next_grid(i, j) = ALIVE
                else
                    next_grid(i, j) = DEAD
                end if
            end do
        end do
    end subroutine cpu_gol_step


    subroutine cpu_gol(initial_state, n_steps, final_state)
        implicit none
        integer, dimension(:, :), intent(in) :: initial_state
        integer, intent(in) :: n_steps
        integer, dimension(:, :), intent(out) :: final_state

        integer :: n, m, i
        integer, dimension(:,:), allocatable, target :: current_grid, next_grid
        integer, dimension(:,:), pointer :: p_current, p_next, p_tmp

        n = size(initial_state, 1)
        m = size(initial_state, 2)

        allocate(current_grid(n, m), next_grid(n, m))

        current_grid = initial_state
        p_current => current_grid
        p_next => next_grid

        do i = 1, n_steps
            ! call print_grid(p_current)
            call cpu_gol_step(p_current, p_next)
            ! TODO visualise ascii
            p_tmp => p_current
            p_current => p_next
            p_next => p_tmp
        end do
        final_state = p_current
        deallocate(current_grid, next_grid)
    end subroutine cpu_gol

end module cpu_game_of_life_mod
