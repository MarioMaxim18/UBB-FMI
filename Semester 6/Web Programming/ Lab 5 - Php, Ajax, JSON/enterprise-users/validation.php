<?php
declare(strict_types=1);

function validate_user_input(array $fields, bool $requirePassword): ?string
{
    $name = $fields['name'];
    $username = $fields['username'];
    $password = $fields['password'];
    $age = $fields['age'];
    $role = $fields['role'];
    $profile = $fields['profile'];
    $email = $fields['email'];
    $webpage = $fields['webpage'];

    $lenName = function_exists('mb_strlen') ? mb_strlen($name) : strlen($name);
    if ($lenName < 2 || $lenName > 100) {
        return 'Name must be between 2 and 100 characters.';
    }
    if (!preg_match('/^[\p{L}\s\-\'\.]+$/u', $name)) {
        return 'Name may only contain letters, spaces, hyphens, apostrophes, and periods.';
    }

    if (!preg_match('/^[A-Za-z0-9_]{3,30}$/', $username)) {
        return 'Username must be 3–30 characters (letters, digits, underscore only).';
    }

    if ($requirePassword) {
        if (strlen($password) < 8) {
            return 'Password must be at least 8 characters.';
        }
        if (strlen($password) > 128) {
            return 'Password must be at most 128 characters.';
        }
    } elseif ($password !== '') {
        if (strlen($password) < 8) {
            return 'New password must be at least 8 characters, or leave blank to keep the current one.';
        }
        if (strlen($password) > 128) {
            return 'Password must be at most 128 characters.';
        }
    }

    if ($age !== 0 && ($age < 18 || $age > 90)) {
        return 'Age must be between 18 and 90, or left empty.';
    }

    $allowedRoles = ['Admin', 'Manager', 'Developer'];
    if (!in_array($role, $allowedRoles, true)) {
        return 'Invalid role.';
    }

    $lenProfile = function_exists('mb_strlen') ? mb_strlen($profile) : strlen($profile);
    if ($lenProfile > 2000) {
        return 'Profile description must be at most 2000 characters.';
    }

    if ($email !== '' && !filter_var($email, FILTER_VALIDATE_EMAIL)) {
        return 'Invalid email address.';
    }

    if ($webpage !== '' && !filter_var($webpage, FILTER_VALIDATE_URL)) {
        return 'Invalid webpage URL (use http:// or https://).';
    }

    return null;
}
