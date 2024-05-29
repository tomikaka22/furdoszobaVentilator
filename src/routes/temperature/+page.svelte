<script>
	import { Splide, SplideSlide } from '@splidejs/svelte-splide';
	import '@splidejs/svelte-splide/css/core';
	import { invalidateAll } from '$app/navigation';
	import { fade } from 'svelte/transition';

	export let data;

	let form;

	async function submit(humidity) {
		form.temperature.value = humidity;
		const formData = new FormData(form);

		const response = await fetch(form.action, {
			method: 'POST',
			body: formData
		});

		if (response.ok)
			invalidateAll();
	}

</script>

<main class="absolute top-0 bottom-0 left-0 right-0 -z-10 flex flex-col justify-center items-center">
	<form bind:this={form} class="hidden" method="POST" action="https://furdo.szoba/post">
		<input type="number" name="temperature">
	</form>

	<div class="w-full flex items-center flex-col gap-4 mb-10">
		<h1 class="font-semibold text-3xl text-primary">Hőmérséklet</h1>
		<Splide class="h-full w-32 rounded-3xl outline outline-primary" on:moved={e => { submit(99 - e.detail.index); }} options={{ arrows: false, pagination: false, direction: 'ttb', height: '12rem', perMove: 1, perPage: 3, start: 99 - data.thresh }}>
			{#each new Array(101) as _, i}
				<SplideSlide class="flex justify-center items-center font-semibold text-2xl text-outline">
						<p class:text-primary={ data.thresh === 100 - i}>
							{100-i}˚C
						</p>
				</SplideSlide>
			{/each}
		</Splide>

		<div class="text-center">
			<p>
				Ha a <b class="text-lg text-primary">hőmérséklet</b>
				{#key data.thresh}
					<span in:fade class="text-lg font-extrabold text-primary inline-block"> {'< ' + data.thresh}˚C</span>
				{/key}
			</p>
			<p>A ventilátor <b class="text-lg text-primary">kikapcsol.</b></p>
		</div>
	</div>

</main>