# System Class
## The system class provides an easier interface for acessing the system password information

# Passwords

## min_pass_age()
Returns the minimum age of a password in seconds (int)

## max_pass_age()
Returns how old a password can be before it needs to be changed in seconds (int)

## complex_pass_req()
Returns if passwords have to be complex (bool)

## unsafe_pass_storage()
Returns if passwords are stored using reversable encryption (bool)

# Accounts

## admin_account_on()
Returns if the administrator account can be logged onto (bool)

## guest_account_on()
Returns if the guest account can be logged onto (bool)

# Users

## get_users()
Returns a list of *psudo*-normal accounts (Accounts that can be logged onto. This might accidentily include some system accounts) (Vector\<User>)