<script>
	import '../app.css';
	import { page } from '$app/stores';
	import { invalidateAll } from '$app/navigation';
	import { fade } from 'svelte/transition';

	export let data;
	setInterval(invalidateAll, 2500);

</script>

	<main>

		<div class="bg-secondary-container bg-opacity-50 w-full h-14 rounded-b-full flex items-center justify-between px-14 font-semibold text-lg">
			<div class="transition-all rounded-xl flex justify-center items-center gap-2 w-24 text-center outline outline-1 outline-on-secondary-container text-on-secondary-container px-4 py-0.5">
				{data.hum}%
				<svg xmlns="http://www.w3.org/2000/svg" height="20px" fill="currentColor" viewBox="160 -880 640 800">
					<path d="M580-240q25 0 42.5-17.5T640-300q0-25-17.5-42.5T580-360q-25 0-42.5 17.5T520-300q0
						25 17.5 42.5T580-240Zm-202-2 260-260-56-56-260 260 56 56Zm2-198q25 0 42.5-17.5T440-500q0-25-17.5-42.5T380-560q-25
						0-42.5 17.5T320-500q0 25 17.5 42.5T380-440ZM480-80q-137 0-228.5-94T160-408q0-100 79.5-217.5T480-880q161 137 240.5
						254.5T800-408q0 140-91.5 234T480-80Zm0-80q104 0 172-70.5T720-408q0-73-60.5-165T480-774Q361-665 300.5-573T240-408q0
						107 68 177.5T480-160Zm0-320Z"
					/>
				</svg>
			</div>

			<div class="p-1">
				{#key data.relay, $page.route.id}
					<svg class:rotating={data.relay && $page.route.id !== '/'} xmlns="http://www.w3.org/2000/svg" height="28px" class="transition-all" fill="currentColor" viewBox="80 -880 800 800">
						<path d="M424-80q-51 0-77.5-30.5T320-180q0-26 11.5-50.5T367-271q22-14 35.5-36t18.5-47l-12-6q-6-3-11-7l-92
							33q-17 6-33 10t-33 4q-63 0-111.5-55T80-536q0-51 30.5-77.5T179-640q26 0 51 11.5t41 35.5q14 22 36 35.5t47
							18.5l6-12q3-6 7-11l-33-92q-6-17-10-33t-4-32q0-64 55-112.5T536-880q51 0 77.5 30.5T640-781q0 26-11.5 51T593-689q-22
							14-35.5 36T539-606l12 6q6 3 11 7l92-34q17-6 32.5-9.5T719-640q81 0 121 67t40 149q0 51-32 77.5T777-320q-25
							0-48.5-11.5T689-367q-14-22-36-35.5T606-421l-6 12q-3 6-7 11l33 92q6 16 10 30.5t4 30.5q1 65-54 115T424-80Zm56-340q25
							0 42.5-17.5T540-480q0-25-17.5-42.5T480-540q-25 0-42.5 17.5T420-480q0 25 17.5 42.5T480-420Zm-46-192q6-2 12.5-3.5T459-618q8-42
							30.5-78t59.5-60q5-4 8-10t3-15q0-8-6-13.5t-18-5.5q-38 0-86 16.5T400-719q0 9 2.5 17t4.5 15l27 75ZM240-400q14
							0 33-7l75-27q-2-6-3.5-12.5T342-459q-42-8-78-30.5T204-549q-4-5-10.5-8t-14.5-3q-9 0-14 6t-5 18q0 54 20.5 95t59.5
							41Zm184 240q47 0 92.5-19t43.5-66q0-8-2.5-15t-4.5-13l-27-75q-6 2-12.5 3.5T501-342q-8 42-30.5 78T411-204q-5 4-8.5 10.5T400-180q1
							8 6 14t18 6Zm353-240q9 0 16-5t7-19q0-38-16-86.5T719-560q-9 0-17 2t-15 4l-75 28q2 6 3.5 12.5T618-501q42 8 78 30.5t60 59.5q3 5 9
							8t12 3ZM618-501ZM459-618ZM342-459Zm159 117Z"
						/>
					</svg>
				{/key}
			</div>

			<div class="transition-all rounded-xl w-24 text-center outline outline-1 outline-on-secondary-container text-on-secondary-container px-4 py-0.5">
				{data.temp} ˚C
			</div>
		</div>

	</main>

	{#key $page.url.pathname}
		<div in:fade={{ duration: 200 }}>
			<slot />
		</div>
	{/key}

	<div class="bg-foreground text-on-background grid grid-cols-4 gap-8 justify-evenly justify-items-center fixed bottom-0 w-full text-sm h-[5.25rem] transition-all duration-200 px-5 pt-3 z-10">
		<a href="/" class="flex flex-col justify-center items-center h-16 w-full transition-all" class:active-nav={$page.route.id === '/'}>
			<div class="w-1/2 h-1/2 flex justify-center items-center rounded-3xl py-1" class:active-img={$page.route.id === '/'} style="transition-timing-function: cubic-bezier(0.05, 0.7, 0.1, 1.0);">
				{#if $page.route.id === '/'}
					<svg class="h-full w-full text-primary" fill="currentColor" xmlns="http://www.w3.org/2000/svg" height="48" viewBox="0 -960 960 960" width="48"><path d="M160-120v-480l320-240 320 240v480H560v-280H400v280H160Z"/></svg>
				{:else}
					<svg class="h-full w-full text-secondary" fill="currentColor" xmlns="http://www.w3.org/2000/svg" height="48" viewBox="0 -960 960 960" width="48"><path d="M220-180h150v-250h220v250h150v-390L480-765 220-570v390Zm-60 60v-480l320-240 320 240v480H530v-250H430v250H160Zm320-353Z"/></svg>
				{/if}
			</div>
			<div class="w-full h-1/2 flex justify-center items-center" class:active-text={$page.route.id === '/'}>
				Főoldal
			</div>
		</a>

		<a href="/fan" class="flex flex-col justify-center items-center h-16 w-full transition-all" class:active-nav={$page.route.id === '/fan'}>
			<div class="w-1/2 h-1/2 flex justify-center items-center rounded-3xl py-1" class:active-img={$page.route.id === '/fan'} style="transition-timing-function: cubic-bezier(0.05, 0.7, 0.1, 1.0);">
				{#if $page.route.id === '/fan'}
					<svg class="h-full w-full text-primary" fill="currentColor" xmlns="http://www.w3.org/2000/svg" height="48" width="48" viewBox="0 -960 960 960"><path d="M360-840v-80h240v80H360Zm80 440h80v-240h-80v240Zm40 320q-74 0-139.5-28.5T226-186q-49-49-77.5-114.5T120-440q0-74 28.5-139.5T226-694q49-49 114.5-77.5T480-800q62 0 119 20t107 58l56-56 56 56-56 56q38 50 58 107t20 119q0 74-28.5 139.5T734-186q-49 49-114.5 77.5T480-80Z"/></svg>
				{:else}
					<svg class="h-full w-full text-secondary" fill="currentColor" xmlns="http://www.w3.org/2000/svg" height="48" width="48" viewBox="0 -960 960 960"><path d="M360-840v-80h240v80H360Zm80 440h80v-240h-80v240Zm40 320q-74 0-139.5-28.5T226-186q-49-49-77.5-114.5T120-440q0-74 28.5-139.5T226-694q49-49 114.5-77.5T480-800q62 0 119 20t107 58l56-56 56 56-56 56q38 50 58 107t20 119q0 74-28.5 139.5T734-186q-49 49-114.5 77.5T480-80Zm0-80q116 0 198-82t82-198q0-116-82-198t-198-82q-116 0-198 82t-82 198q0 116 82 198t198 82Zm0-280Z"/></svg>
				{/if}
			</div>
			<div class="w-full h-1/2 flex justify-center items-center" class:active-text={$page.route.id === '/fan'}>
				Időzítő
			</div>
		</a>

		<a href="/humidity" class="flex flex-col justify-center items-center h-16 w-full transition-all" class:active-nav={$page.route.id === '/humidity'}>
			<div class="w-1/2 h-1/2 flex justify-center items-center rounded-3xl py-1" class:active-img={$page.route.id === '/humidity'} style="transition-timing-function: cubic-bezier(0.05, 0.7, 0.1, 1.0);">
				{#if $page.route.id === '/humidity'}
					<svg class="h-full w-full text-primary" fill="currentColor" xmlns="http://www.w3.org/2000/svg" height="48" width="48" viewBox="160 -880 640 800"><path d="M580-240q25 0 42.5-17.5T640-300q0-25-17.5-42.5T580-360q-25 0-42.5 17.5T520-300q0 25 17.5 42.5T580-240Zm-202-2 260-260-56-56-260 260 56 56Zm2-198q25 0 42.5-17.5T440-500q0-25-17.5-42.5T380-560q-25 0-42.5 17.5T320-500q0 25 17.5 42.5T380-440ZM480-80q-137 0-228.5-94T160-408q0-100 79.5-217.5T480-880q161 137 240.5 254.5T800-408q0 140-91.5 234T480-80Z"/></svg>
				{:else}
					<svg class="h-full w-full text-secondary" fill="currentColor" xmlns="http://www.w3.org/2000/svg" height="48" width="48" viewBox="160 -880 640 800"><path d="M580-240q25 0 42.5-17.5T640-300q0-25-17.5-42.5T580-360q-25 0-42.5 17.5T520-300q0 25 17.5 42.5T580-240Zm-202-2 260-260-56-56-260 260 56 56Zm2-198q25 0 42.5-17.5T440-500q0-25-17.5-42.5T380-560q-25 0-42.5 17.5T320-500q0 25 17.5 42.5T380-440ZM480-80q-137 0-228.5-94T160-408q0-100 79.5-217.5T480-880q161 137 240.5 254.5T800-408q0 140-91.5 234T480-80Zm0-80q104 0 172-70.5T720-408q0-73-60.5-165T480-774Q361-665 300.5-573T240-408q0 107 68 177.5T480-160Zm0-320Z"/></svg>
				{/if}
			</div>
			<div class="w-full h-1/2 flex justify-center items-center" class:active-text={$page.route.id === '/humidity'}>
				Pára
			</div>
		</a>

		<a href="/temperature" class="flex flex-col justify-center items-center h-16 w-full transition-all" class:active-nav={$page.route.id === '/temperature'}>
			<div class="w-1/2 h-1/2 flex justify-center items-center rounded-3xl py-1" class:active-img={$page.route.id === '/temperature'} style="transition-timing-function: cubic-bezier(0.05, 0.7, 0.1, 1.0);">
				{#if $page.route.id === '/temperature'}
					<svg class="h-full w-full text-primary" fill="currentColor" xmlns="http://www.w3.org/2000/svg" height="48" width="48" viewBox="280 -840 400 720"><path d="M480-120q-83 0-141.5-58.5T280-320q0-48 21-89.5t59-70.5v-240q0-50 35-85t85-35q50 0 85 35t35 85v240q38 29 59 70.5t21 89.5q0 83-58.5 141.5T480-120Zm-40-440h80v-160q0-17-11.5-28.5T480-760q-17 0-28.5 11.5T440-720v160Z"/></svg>
				{:else}
					<svg class="h-full w-full text-secondary" fill="currentColor" xmlns="http://www.w3.org/2000/svg" height="48" width="48" viewBox="280 -840 400 720"><path d="M480-120q-83 0-141.5-58.5T280-320q0-48 21-89.5t59-70.5v-240q0-50 35-85t85-35q50 0 85 35t35 85v240q38 29 59 70.5t21 89.5q0 83-58.5 141.5T480-120Zm0-80q50 0 85-35t35-85q0-29-12.5-54T552-416l-32-24v-280q0-17-11.5-28.5T480-760q-17 0-28.5 11.5T440-720v280l-32 24q-23 17-35.5 42T360-320q0 50 35 85t85 35Zm0-120Z"/></svg>
				{/if}
			</div>
			<div class="w-full h-1/2 flex justify-center items-center" class:active-text={$page.route.id === '/temperature'}>
				Hőfok
			</div>
		</a>
	</div>

<style lang="postcss">
	:global(*) {
		-webkit-tap-highlight-color: transparent;
		scrollbar-width: none;
	}

	:global(*)::-webkit-scrollbar {
		display: none;
	}

	:global(body) {
		background-color: #201a17;
		@apply text-secondary;
	}

	.rotating {
		animation: rotating .8s linear infinite;
	}

	@keyframes rotating {
		from {
			transform: rotate(0deg);
		}
		to {
			transform: rotate(360deg);
		}
	}

	.active-nav {
		@apply font-semibold;
	}

	.active-img {
		@apply
		bg-secondary-container
		w-full
		transition-all
		duration-300
		;
	}

	.active-text {
		@apply
		text-secondary
		transition-all
		duration-200
		;
	}
</style>